
using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Xml;

namespace SceneMaster.Scenes.Models
{

    public class Scene : ObservableObject, IDisposable
    {
        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();

        [Browsable(false)]
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        public TiledMapWrapper ForegroundTiledMap { get; } = new(isForeground:true);
        public TiledMapWrapper BackgroundTiledMap { get; } = new(isForeground:false);

        private const string ForegroundTiledMapFilePathNodeName = "ForegroundTiledMapFilePath";
        private const string BackgroundTiledMapFilePathNodeName = "BackgroundTiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";
        //private const string TerrainNodeName = "Terrain";

        public Scene(/*List<BitmapImage> tileTypeImages*/)
        {
            //m_tileTypeImages = tileTypeImages;

            ForegroundTiledMap.PropertyChanged += ForegroundTiledMap_PropertyChanged;
            BackgroundTiledMap.PropertyChanged += BackgroundTiledMap_PropertyChanged;
        }

        private void ForegroundTiledMap_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            OnPropertyChanged(nameof(ForegroundTiledMap));
        }

        private void BackgroundTiledMap_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            OnPropertyChanged(nameof(BackgroundTiledMap));
        }

        public void ImportTiledMap(string tiledMapFilePath)
        {
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            ForegroundTiledMap.LoadTiledMap(tiledMapFilePath);
            //BuildTerrain();
        }


        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var foregroundFilePathNode = root[ForegroundTiledMapFilePathNodeName];
            if (foregroundFilePathNode != null && !string.IsNullOrEmpty(foregroundFilePathNode.InnerText))
            {
                string tiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), foregroundFilePathNode.InnerText);
                ForegroundTiledMap.LoadTiledMap(tiledMapFilePath);
            }

            var backgroundFilePathNode = root[BackgroundTiledMapFilePathNodeName];
            if (backgroundFilePathNode != null && !string.IsNullOrEmpty(backgroundFilePathNode.InnerText))
            {
                string tiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), backgroundFilePathNode.InnerText);
                BackgroundTiledMap.LoadTiledMap(tiledMapFilePath);
            }

            var editorObjectsNode = root[EditorObjectsNodeName];
            if (editorObjectsNode != null)
            {
                foreach (var editorObjectNode in editorObjectsNode.ChildNodes.OfType<XmlElement>())
                {
                    string nodeType = editorObjectNode.Name;
                    EditorObject editorObject = null;

                    try
                    {
                        switch (nodeType) 
                        {
                        case nameof(EditorObjectType.GameObject):
                            editorObject = new GameObject(editorObjectNode, editorObjectLibraryViewModel.GameObjectTemplateLibrary);
                        break;
                        case nameof(EditorObjectType.Command):
                            editorObject = new CommandObject(editorObjectNode, editorObjectLibraryViewModel.CommandLibrary);
                        break;
                        }
                    }
                    catch (Exception) 
                    {
                        Console.WriteLine($"Error trying to load {nodeType}");
                        continue;
                    }

                    EditorObjects.Add(editorObject);
                }
            }
        }

        internal void SaveToXmlElement(XmlDocument doc, XmlElement root, string filePath)
        {
            // foregroundtiled map file path
            var foregroundFilePathNode = doc.CreateElement(ForegroundTiledMapFilePathNodeName);
            foregroundFilePathNode.InnerText = string.IsNullOrEmpty(ForegroundTiledMap.TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), ForegroundTiledMap.TiledMapFilePath);
            root.AppendChild(foregroundFilePathNode);

            // background tiled map file path
            var backgroundFilePathNode = doc.CreateElement(BackgroundTiledMapFilePathNodeName);
            backgroundFilePathNode.InnerText = string.IsNullOrEmpty(BackgroundTiledMap.TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), BackgroundTiledMap.TiledMapFilePath);
            root.AppendChild(backgroundFilePathNode);

            // gameobjects
            var editorObjectsNode = doc.CreateElement(EditorObjectsNodeName);
            root.AppendChild(editorObjectsNode);

            foreach (var editorObject in EditorObjects)
            {
                var editorObjectNode = editorObject.SaveToXml(doc);
                editorObjectsNode.AppendChild(editorObjectNode);
            }
        }

        internal EditorObject CreateEditorObject(int x, int y, EditorObjectInfo editorObjectInfo)
        {
            var editorObject = editorObjectInfo.CreateEditorObject(x, y, this);

            if (editorObject == null)
                return null;

            EditorObjects.Add(editorObject);
            OnPropertyChanged(nameof(EditorObjects));

            return editorObject;
        }

        public void Dispose()
        {
            ForegroundTiledMap.Dispose();
            BackgroundTiledMap.Dispose();
        }
    }
}