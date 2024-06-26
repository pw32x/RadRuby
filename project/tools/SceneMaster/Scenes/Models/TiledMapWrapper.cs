﻿
using CommunityToolkit.Mvvm.ComponentModel;
using PropertyTools.DataAnnotations;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Scenes.ViewModels;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using TiledCS;

namespace SceneMaster.Scenes.Models
{
    public class TiledMapWrapper : ObservableObject, IDisposable
    {
        FileSystemWatcher m_tiledMapFileWatcher = null;

        private TiledMap m_tiledMap;
        private string m_tiledMapDirectory;

        [PropertyTools.DataAnnotations.Browsable(false)]
        public TiledMap TiledMap { get => m_tiledMap; private set => SetProperty(ref m_tiledMap, value); }

        private Dictionary<int, TiledTileset> m_tiledMapTilesets;
        private IEnumerable<TiledLayer> m_tileMapTileLayers;
        private Dictionary<string, BitmapSource> m_tilesetBitmaps;

        // visual of the actual Tiled map
        private WriteableBitmap m_tiledMapBitmapSource;

        [PropertyTools.DataAnnotations.DisplayName("Preview")]
        public WriteableBitmap TiledMapBitmapSource { get => m_tiledMapBitmapSource; private set => SetProperty(ref m_tiledMapBitmapSource, value); }

        [PropertyTools.DataAnnotations.Browsable(false)]
        public bool IsForeground { get; }= false;

        private string m_tiledMapFilePath = "";

        [InputFilePath(".tmx", "Tmx files|*.tmx;")]
        public string TiledMapFilePath
        {
            get => m_tiledMapFilePath;
            set
            {
                LoadTiledMap(value, Guid.Empty);
                TiledMapFilename = Path.GetFileName(m_tiledMapFilePath);
            }
        }

        private string m_tiledMapFilename = "";
        private System.Windows.Media.Color m_transparentColor;

        [PropertyTools.DataAnnotations.Browsable(false)]
        public string TiledMapFilename
        {
            get => m_tiledMapFilename;
            private set => SetProperty(ref m_tiledMapFilename, value);
        }

        private SceneViewModel m_sceneViewModel;

        public TiledMapWrapper(SceneViewModel sceneViewModel, bool isForeground)
        {
            m_sceneViewModel = sceneViewModel;
            m_sceneViewModel.EditorObjectViewModels.CollectionChanged += EditorObjects_CollectionChanged;
            IsForeground = isForeground;
        }

        private void EditorObjects_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            OnPropertyChanged("Scrollers");
            OnPropertyChanged("ScrollerGuid");
        }

        [PropertyTools.DataAnnotations.Browsable(false)]
        public IEnumerable<GameObjectViewModel> Scrollers => m_sceneViewModel.EditorObjectViewModels.OfType<GameObjectViewModel>().Where(g => g.GameObject.GameObjectTemplate.GameObjectType == GameObjectType.Scroller);

        private GameObjectViewModel m_scroller;

        [ItemsSourceProperty("Scrollers")]
        [DisplayMemberPath("GameObject.Name")]
        [PropertyTools.DataAnnotations.DisplayName("Scroller")]
        [SelectedValuePath("GameObject.Guid")]
        public Guid ScrollerGuid
        { 
            get => m_scroller?.GameObject?.Guid ?? Guid.Empty; 
            set
            {
                if (m_scroller != null) 
                {
                    m_scroller.PropertyChanged -= M_scroller_PropertyChanged;
                }

                m_scroller = Scrollers.FirstOrDefault(s => s.GameObject.Guid == value);

                OnPropertyChanged(nameof(ScrollerGuid));
                OnPropertyChanged(nameof(Scroller));

                if (m_scroller != null)
                {
                    m_scroller.PropertyChanged += M_scroller_PropertyChanged;
                }
            }
        }

        [PropertyTools.DataAnnotations.Browsable(false)]
        public GameObjectViewModel Scroller 
        { 
            get => m_scroller; 
        }

        private void M_scroller_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            //if (e.PropertyName == nameof(GameObjectViewModel.Name)) 
            //{
            //    OnPropertyChanged(nameof(ScrollerGuid));
            //}
        }

        private void ShutdownTiledMap()
        {
            m_tiledMap = null;
            m_tiledMapDirectory = null;
            m_tileMapTileLayers = null;
            m_tiledMapTilesets = null;
            m_tilesetBitmaps = null;
            TiledMapBitmapSource = null;
            //m_terrain.Clear();
        }



        public void LoadTiledMap(string tiledMapFilePath, Guid scrollerGuid)
        {
            StopWatchingTiledMap();

            try
            {
                ShutdownTiledMap();

                m_scroller = null;

                m_tiledMapFilePath = tiledMapFilePath;

                m_tiledMap = new TiledMap(tiledMapFilePath);

                m_tiledMapDirectory = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tiledMapFilePath));

                m_tiledMapTilesets = m_tiledMap.GetTiledTilesets(m_tiledMapDirectory);
                m_tileMapTileLayers = m_tiledMap.Layers.Where(x => x.type == TiledLayerType.TileLayer);

                m_tilesetBitmaps = new Dictionary<string, BitmapSource>();
                foreach (var tileset in m_tiledMapTilesets.Values)
                {
                    string tilesetFolder = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tileset.FilePath));
                    string source = tileset.Image.source;
                    BitmapImage bitmapImage = new BitmapImage();
                    bitmapImage.BeginInit();
                    bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                    bitmapImage.UriSource = new Uri(tilesetFolder + source, UriKind.RelativeOrAbsolute);
                    bitmapImage.EndInit();

                    m_transparentColor = bitmapImage.Palette.Colors[0];

                    FormatConvertedBitmap convertedBitmap = new FormatConvertedBitmap(bitmapImage, 
                                                                                      PixelFormats.Bgra32, 
                                                                                      null, 
                                                                                      0);
                    m_tilesetBitmaps.Add(source, convertedBitmap);
                }

                TiledMapBitmapSource = BuildTiledMapBitmapSource();

                m_scroller = Scrollers.FirstOrDefault(s => s.GameObject.Guid == scrollerGuid);

                StartWatchingTiledMap(tiledMapFilePath);
            }
            catch (Exception e) 
            {
                ShutdownTiledMap();
                m_tiledMapFilePath = "";
                MessageBox.Show("Failed loading " + tiledMapFilePath + ". Error: " + e.Message);
            }

            OnPropertyChanged(nameof(TiledMapFilePath));
        }

        private void StartWatchingTiledMap(string filePath)
        {
            m_tiledMapFileWatcher = new FileSystemWatcher(Path.GetDirectoryName(Path.GetFullPath(filePath)));
            m_tiledMapFileWatcher.Filter = Path.GetFileName(filePath);
            
            // When saving a Tiled map, it saves it under a temporary filename, deletes the original
            // and renames it to the same filename. 
            m_tiledMapFileWatcher.Renamed += M_tiledMapFileWatcher_Renamed;
            m_tiledMapFileWatcher.Changed += M_tiledMapFileWatcher_Changed;
            

            m_tiledMapFileWatcher.EnableRaisingEvents = true;
        }

        private void M_tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath, Scroller?.GameObject?.Guid ?? Guid.Empty); });
        }

        private void M_tiledMapFileWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath, Scroller?.GameObject?.Guid ?? Guid.Empty); });
        }

        private void StopWatchingTiledMap()
        {
            if (m_tiledMapFileWatcher == null)
                return;

            m_tiledMapFileWatcher.EnableRaisingEvents = false;
            m_tiledMapFileWatcher.Changed -= tiledMapFileWatcher_Changed;
            m_tiledMapFileWatcher.Dispose();
            m_tiledMapFileWatcher = null;
        }

        private void tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            
        }


        private WriteableBitmap BuildTiledMapBitmapSource()
        {
            WriteableBitmap writeableBitmap = new WriteableBitmap(m_tiledMap.Width * m_tiledMap.TileWidth,
                                                                 m_tiledMap.Height * m_tiledMap.TileHeight,
                                                                 96,
                                                                 96,
                                                                 PixelFormats.Bgra32,
                                                                 null);

            try
            {
                writeableBitmap.Lock();

                foreach (var layer in m_tileMapTileLayers)
                {
                    for (var tileY = 0; tileY < layer.height; tileY++)
                    {
                        for (var tileX = 0; tileX < layer.width; tileX++)
                        {
                            var index = tileY * layer.width + tileX; // Assuming the default render order is used which is from right to bottom
                            var gid = layer.data[index]; // The tileset tile index

                            DrawTileToBitmapHelper(writeableBitmap, tileX, tileY, gid);
                        }
                    }
                }
            }
            finally
            {
                // Unlock the WriteableBitmap when done
                writeableBitmap.Unlock();
            }

            return writeableBitmap;
        }

        /*
        private void DrawTileToBitmap(WriteableBitmap writeableBitmap, int tileX, int tileY, int gid)
        {
            try
            {
                writeableBitmap.Lock();

                DrawTileToBitmapHelper(writeableBitmap, tileX, tileY, gid);
            }
            finally
            {
                // Unlock the WriteableBitmap when done
                writeableBitmap.Unlock();
            }
        }
        */

        private void DrawTileToBitmapHelper(WriteableBitmap writeableBitmap, int tileX, int tileY, int gid)
        {
            // Gid 0 is used to tell there is no tile set
            if (gid == 0)
            {
                return;
            }

            // Helper method to fetch the right TieldMapTileset instance. 
            // This is a connection object Tiled uses for linking the correct tileset to the gid value using the firstgid property.
            var mapTileset = m_tiledMap.GetTiledMapTileset(gid);

            // Retrieve the actual tileset based on the firstgid property of the connection object we retrieved just now
            var tileset = m_tiledMapTilesets[mapTileset.firstgid];

            // Use the connection object as well as the tileset to figure out the source rectangle.
            var rect = m_tiledMap.GetSourceRect(mapTileset, tileset, gid);

            // Render gameobject at position tileX, tileY using the rect

            var bitmapImage = m_tilesetBitmaps[tileset.Image.source];

            // Copy pixel data from the BitmapImage to the WriteableBitmap
            Int32Rect sourceRect = new Int32Rect(rect.x, rect.y, rect.width, rect.height);
            var stride = (sourceRect.Width * bitmapImage.Format.BitsPerPixel + 7) / 8; // here

            byte[] pixelData = new byte[stride * sourceRect.Height];
            bitmapImage.CopyPixels(sourceRect, pixelData, stride, 0);

            if (IsForeground)
            {
                for (int loop = 0; loop < pixelData.Length; loop += 4)
                {
                    if (pixelData[loop] == m_transparentColor.B &&
                        pixelData[loop + 1] == m_transparentColor.G &&
                        pixelData[loop + 2] == m_transparentColor.R)
                    {
                        pixelData[loop + 3] = 0;
                    }
                }
            }

            Int32Rect destRect = new Int32Rect(tileX * m_tiledMap.TileWidth,
                                               tileY * m_tiledMap.TileHeight,
                                               m_tiledMap.TileWidth,
                                               m_tiledMap.TileHeight);



            writeableBitmap.WritePixels(destRect,
                                        pixelData,
                                        stride,
                                        0);
        }

        public void Dispose()
        {
            StopWatchingTiledMap();
        }

        /*
        public const int TILE_EMPTY = 0;
        public const int TILE_SOLID = 1;
        public const int TILE_TOPSOLID = 2;
        public const int TILE_CLIMB = 3;
        public const int TILE_HURT = 4;
        public const int TILE_SLOPE45RIGHT = 5;
        public const int TILE_SLOPE45LEFT = 6;
        public const int TILE_SLOPE30RIGHT1 = 7;
        public const int TILE_SLOPE30RIGHT2 = 8;
        public const int TILE_SLOPE30LEFT1 = 9;
        public const int TILE_SLOPE30LEFT2 = 10;
        public const int TILE_WATER = 11;

        static public Dictionary<string, int> TileTypeNameToInt = new Dictionary<string, int>()
        {
            {"empty",           0},
            {"solid",           1},
            {"topsolid",        2},
            {"climb",           3},
            {"hurt",            4},
            {"slope45right",    5},
            {"slope45left",     6},
            {"slope30right1",   7},
            {"slope30right2",   8},
            {"slope30left1",    9},
            {"slope30left2",    10},
            {"water",           11}
        };

        public static string TileAttributeToString(int tileAttribute)
        {
            switch (tileAttribute)
            {
                case TILE_SOLID: return "solid";
                case TILE_TOPSOLID: return "topsolid";
                case TILE_CLIMB: return "climb";
                case TILE_HURT: return "hurt";
                case TILE_SLOPE45RIGHT: return "slope45right";
                case TILE_SLOPE45LEFT: return "slope45left";
                case TILE_SLOPE30RIGHT1: return "slope30right1";
                case TILE_SLOPE30RIGHT2: return "slope30right2";
                case TILE_SLOPE30LEFT1: return "slope30left1";
                case TILE_SLOPE30LEFT2: return "slope30left2";
                case TILE_WATER: return "water";
            }

            return "";
        }

        List<BitmapImage> m_tileTypeImages;

        List<int> m_terrain = new List<int>();
        int m_terrainWidth = 0;
        int m_terrainHeight = 0;

        private WriteableBitmap m_terrainBitmapSource;
        public WriteableBitmap TerrainBitmapSource { get => m_terrainBitmapSource; private set => SetProperty(ref m_terrainBitmapSource, value); }
        */


        /*
        public void SetTerrainTileType(int tileX, int tileY, int tileType)
        {
            m_terrain[tileX + (tileY * m_terrainWidth)] = tileType;
            var bitmapImage = m_tileTypeImages[tileType];

            DrawBitmapHelper(TerrainBitmapSource, tileX, tileY, bitmapImage);

            OnPropertyChanged(nameof(TerrainBitmapSource));
        }

        private void BuildTerrain()
        {
            m_terrain.Clear();

            var layer = m_tileMapTileLayers.First();

            m_terrain.Capacity = layer.width * layer.height;

            m_terrainWidth = layer.width;
            m_terrainHeight = layer.height;

            for (var tileY = 0; tileY < m_terrainHeight; tileY++)
            {
                for (var tileX = 0; tileX < m_terrainWidth; tileX++)
                {
                    var index = tileY * layer.width + tileX; // Assuming the default render order is used which is from right to bottom
                    var gid = layer.data[index]; // The tileset tile index

                    // Gid 0 is used to tell there is no tile set
                    if (gid == 0)
                    {
                        return;
                    }

                    // Helper method to fetch the right TieldMapTileset instance. 
                    // This is a connection object Tiled uses for linking the correct tileset to the gid value using the firstgid property.
                    var mapTileset = m_tiledMap.GetTiledMapTileset(gid);

                    // Retrieve the actual tileset based on the firstgid property of the connection object we retrieved just now
                    var tileset = m_tiledMapTilesets[mapTileset.firstgid];

                    // Use the connection object as well as the tileset to figure out the source rectangle.
                    var tiledTile = m_tiledMap.GetTiledTile(mapTileset, tileset, gid);

                    var property = tiledTile.properties.First();

                    if (!string.IsNullOrEmpty(property.name))
                        m_terrain.Add(TileTypeNameToInt[property.name]);
                    else
                        m_terrain.Add(TILE_EMPTY);
                }
            }

            TerrainBitmapSource = BuildTerrainImage(m_tileTypeImages);
        }

        private WriteableBitmap BuildTerrainImage(List<BitmapImage> tileTypeImages)
        {
            WriteableBitmap writeableBitmap = new WriteableBitmap(m_tiledMap.Width * m_tiledMap.TileWidth,
                                                                 m_tiledMap.Height * m_tiledMap.TileHeight,
                                                                 96,
                                                                 96,
                                                                 PixelFormats.Bgra32,
                                                                 null);

            for (var tileY = 0; tileY < m_terrainHeight; tileY++)
            {
                for (var tileX = 0; tileX < m_terrainWidth; tileX++)
                {

                    var tileType = m_terrain[tileX + (tileY * m_terrainWidth)];

                    var bitmapImage = tileTypeImages[tileType];
                    DrawBitmapHelper(writeableBitmap, tileX, tileY, bitmapImage);
                }
            }

            return writeableBitmap;
        }
        
        private void DrawBitmapHelper(WriteableBitmap writeableBitmap, int tileX, int tileY, BitmapImage bitmapImage)
        {
            // Copy pixel data from the BitmapImage to the WriteableBitmap
            Int32Rect sourceRect = new Int32Rect(0,
                                                 0,
                                                 m_tiledMap.TileWidth,
                                                 m_tiledMap.TileHeight);
            var stride = (sourceRect.Width * bitmapImage.Format.BitsPerPixel + 7) / 8; // here

            byte[] pixelData = new byte[stride * sourceRect.Height];
            bitmapImage.CopyPixels(sourceRect, pixelData, stride, 0);

            Int32Rect destRect = new Int32Rect(tileX * m_tiledMap.TileWidth,
                                               tileY * m_tiledMap.TileHeight,
                                               m_tiledMap.TileWidth,
                                               m_tiledMap.TileHeight);

            writeableBitmap.WritePixels(destRect,
                                        pixelData,
                                        stride,
                                        0);
        }
        */
    }
}