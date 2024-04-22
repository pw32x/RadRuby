using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace tmx2c
{
    public class Map
    {
        public enum ExportMode
        {
            Map,
            StripMap
        }

        public string MapName { get; private set; }
        public string MapFilename { get; private set; }

        // get the data we want from the nodes

        string mDestinationSourceFile;
        string mDestinationHeaderFile;

        public int MapWidth { get; private set; }
        public int MapHeight { get; private set; }
        int mTileWidth;
        int mTileHeight;

        private XmlNode mTilemapLayerNode = null;
        private XmlNode mTerrainLayerNode = null;
        private List<XmlNode> mTilesetNodes = new List<XmlNode>();

        const uint TILED_FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        const uint TILED_FLIPPED_VERTICALLY_FLAG = 0x40000000;
        const uint GenesisFlippedHorizontallyFlag = (1 << 11);
        const uint GenesisFlippedVerticallyFlag = (1 << 12);

        public List<string> ActiveLayers { get; private set; }

        public List<Tileset> Tilesets { get; }  = new List<Tileset>();

        void ParseTilesets(List<XmlNode> tilesetNodes, string sourceFolder)
        {
            List<Tileset> mUsedTilesets = new List<Tileset>();

            foreach (var tilesetNode in tilesetNodes)
            {
                if (mUsedTilesets.Count >= 4)
                    throw new Exception("map: " + MapName + " Hit the limit of tilesets to use in a map. ");

                string tilesetFilename = tilesetNode.Attributes["source"].Value;

                // is this a new tileset or a previously seen one?
                Tileset tileset = Tilesets.FirstOrDefault(t => String.Equals(t.TilesetFilename, tilesetFilename, StringComparison.OrdinalIgnoreCase));

                bool newTileset = (tileset == null);

                if (tileset == null)
                {
                    tileset = new Tileset();

                    tileset.TilesetFilename = tilesetFilename;
                    tileset.TilesetName = Path.GetFileNameWithoutExtension(tileset.TilesetFilename);

                    if (tileset.TilesetFilename.Contains("gameobjects.tsx") ||
                        tileset.TilesetFilename.Contains("tiletypes.tsx"))
                    {
                        tileset.IsEditorTileset = true;
                    }
                    else
                    {
                        tileset.TilesetIndex = (uint)mUsedTilesets.Count;
                        mUsedTilesets.Add(tileset);
                        tileset.LoadTileset(tilesetNode.Attributes["source"].Value, sourceFolder);
                    }
                }

                // create the TileIndexStartEnd object and update the previous one.
                var TileIndex = new Tileset.TileIndexStartEnd();

                TileIndex.StartIndex = uint.Parse(tilesetNode.Attributes["firstgid"].Value);

                if (Tilesets.Count > 0)
                    Tilesets.Last().TileIndexes.Last().EndIndex = TileIndex.StartIndex;

                tileset.TileIndexes.Add(TileIndex);


                if (newTileset)
                    Tilesets.Add(tileset);
            }

            /*
            // for each tileset, sort their tilesetindexes so that the one with the lower
            // start index goes first.
            foreach (var tileset in Tilesets)
            {
                tileset.TileIndexes = tileset.TileIndexes.OrderBy(t => t.StartIndex).ToList();
            }
            */

            // remap the tile ranges so that they leave out any stray gameobject indexes
            if (mUsedTilesets.Count > 0)
            {
                var firstTileset = mUsedTilesets[0];
                firstTileset.ExportStartIndex = firstTileset.TileIndexes.First().StartIndex;
                firstTileset.ExportEndIndex = firstTileset.TileIndexes.First().EndIndex;

                for (int loop = 1; loop < mUsedTilesets.Count; loop++)
                {
                    var tileset = mUsedTilesets[loop];
                    var previousTileset = mUsedTilesets[loop - 1];

                    tileset.ExportStartIndex = previousTileset.ExportEndIndex;

                    if (tileset.IsAnimated)
                    {
                        tileset.ExportEndIndex = tileset.ExportStartIndex + 8;//tileset.AnimationTileStride;
                    }
                    else
                    {
                        tileset.ExportEndIndex = tileset.ExportStartIndex +
                                                 (tileset.TileIndexes.First().EndIndex - tileset.TileIndexes.First().StartIndex);
                    }
                }
            }
        }

        public Map(string mapFilename)
        {
            if (String.IsNullOrEmpty(mapFilename))
                throw new Exception("Invalid path passed to Map");

            MapFilename = mapFilename;
            MapName = Path.GetFileNameWithoutExtension(mapFilename);
            string sourceFolder = Path.GetDirectoryName(mapFilename);

            if (!String.IsNullOrEmpty(sourceFolder) && !sourceFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                sourceFolder += Path.DirectorySeparatorChar;

            XmlDocument doc = new XmlDocument();
            doc.Load(mapFilename);

            // find the nodes we're interested in.
            var mapNode = doc.ChildNodes[1];

            MapWidth = int.Parse(mapNode.Attributes["width"].Value);
            MapHeight = int.Parse(mapNode.Attributes["height"].Value);
            mTileWidth = int.Parse(mapNode.Attributes["tilewidth"].Value);
            mTileHeight = int.Parse(mapNode.Attributes["tileheight"].Value);

            if (mTileWidth != 16 && mTileHeight != 16)
                throw new Exception("tile size is not 16 x 16");

            for (int loop = 0; loop < mapNode.ChildNodes.Count; loop++)
            {
                XmlNode childNode = mapNode.ChildNodes[loop];

                switch (childNode.Name)
                {
                    case "tileset":
                        mTilesetNodes.Add(childNode);
                        break;
                    case "layer":
                        {
                            var nameAttribute = childNode.Attributes["name"];

                            var dataNode = childNode.ChildNodes[0];

                            if (nameAttribute != null)
                            {
                                if (nameAttribute.Value.ToLower().Contains("terrain") || nameAttribute.Value.ToLower().Contains("collision"))
                                {
                                    if (mTerrainLayerNode == null)
                                        mTerrainLayerNode = dataNode;
                                    else
                                        Console.WriteLine("tmx2c -  Multiple terrain maps not supported. The layer " + nameAttribute.Value + " will be ignored.");
                                    break;
                                }
                            }

                            if (mTilemapLayerNode == null)
                            {
                                mTilemapLayerNode = dataNode;
                            }
                            else
                            {
                                Console.WriteLine("tmx2c -  Multiple tile maps not supported. Subsequent layers will be ignored.");
                            }
                        }
                        break;
                }
            }

            ParseTilesets(mTilesetNodes, sourceFolder);
        }

        public bool NeedsUpdate(DateTime applicationTime, 
                                DateTime gameObjectsFileTime, 
                                string sourceFolder,
                                string destinationFolder)
        {
            mDestinationSourceFile = destinationFolder + Path.GetFileNameWithoutExtension(MapName) + ".c";
            mDestinationHeaderFile = destinationFolder + Path.GetFileNameWithoutExtension(MapName) + ".h";

            DateTime mapFileDateTime = File.GetLastWriteTime(MapFilename);

            DateTime destinationSourceFileTime = File.GetLastWriteTime(mDestinationSourceFile);
            DateTime destinationHeaderFileTime = File.GetLastWriteTime(mDestinationHeaderFile);

            if (applicationTime > destinationSourceFileTime || applicationTime > destinationHeaderFileTime ||
                mapFileDateTime > destinationSourceFileTime || mapFileDateTime > destinationHeaderFileTime ||
                gameObjectsFileTime > destinationSourceFileTime || gameObjectsFileTime > destinationHeaderFileTime)
            {
                return true;
            }

            foreach (var tileset in Tilesets)
            {
                DateTime tilesetTime = File.GetLastWriteTime(sourceFolder + tileset.TilesetName + ".tsx");

                if (tilesetTime > destinationSourceFileTime || tilesetTime > destinationHeaderFileTime)
                {
                    return true;
                }

                DateTime bitmapFileTime = File.GetLastWriteTime(sourceFolder + tileset.TilesetName + ".bmp");

                if (bitmapFileTime > destinationSourceFileTime || bitmapFileTime > destinationHeaderFileTime)
                {
                    return true;
                }
            }

            return false;
        }

        void ParseProperties(XmlNode properties)
        {
            for (int loop = 0; loop < properties.ChildNodes.Count; loop++)
            {
                XmlNode childNode = properties.ChildNodes[loop];

                if (childNode.Attributes["name"].Value == "activelayers")
                {
                    ActiveLayers = childNode.Attributes["value"].Value.Split().ToList();
                }
            }
        }

        public class Tile
        {
            public Tile()
            {
                Index = 0;
                HorizontalFlip = false;
                VerticalFlip = false;
                Tileset = null;
            }

            public uint Index;
            public bool HorizontalFlip;
            public bool VerticalFlip;
            public Tileset Tileset;
        }

        List<Tile> mTilemap = new List<Tile>();

        void FindTileSetAndIndex(List<Tileset> tilesets, Tile tile, uint tileIndex)
        {
            if (tileIndex == 0)
                return;

            foreach (var tileset in Tilesets)
            {
                foreach (var tilesetIndex in tileset.TileIndexes)
                {
                    if (tileIndex >= tilesetIndex.StartIndex && tileIndex < tilesetIndex.EndIndex && !tileset.IsEditorTileset)
                    {
                        tile.Tileset = tileset;
                        tile.Index = (tileIndex - tilesetIndex.StartIndex) + tileset.TileIndexes.First().StartIndex;
                        return;
                    }
                }
            }

            throw new Exception("Not supposed to be here. Was a game object accidentally used as a tile?");
        }

        void ParseTileMapLayer(XmlNode tilemapLayerNode)
        {
            List<uint> tileValues = tilemapLayerNode.ChildNodes[0].Value.Split(',').Select(uint.Parse).ToList();

            foreach (uint tileValue in tileValues)
            {
                var tile = new Tile();

                tile.HorizontalFlip = (tileValue & TILED_FLIPPED_HORIZONTALLY_FLAG) > 0;
                tile.VerticalFlip = (tileValue & TILED_FLIPPED_VERTICALLY_FLAG) > 0;

                uint tileIndex = tileValue;

                if (tile.HorizontalFlip)
                    tileIndex &= ~TILED_FLIPPED_HORIZONTALLY_FLAG;

                if (tile.VerticalFlip)
                    tileIndex &= ~TILED_FLIPPED_VERTICALLY_FLAG;

                FindTileSetAndIndex(Tilesets, tile, tileIndex);

                mTilemap.Add(tile);
            }
        }

        List<uint> mCollisionMap = new List<uint>();

        void ParseTerrainLayer(XmlNode collisionLayerNode)
        {
            var tileAttributeTileset = Tilesets.FirstOrDefault(t => t.TilesetName.ToLower().Contains("tiletypes"));

            if (tileAttributeTileset == null)
            {
                Console.WriteLine("No tile attribute tiles found for collision layer. Collision layer won't get exported.");
                return;
            }

            List<uint> tileCollisionValues = collisionLayerNode.ChildNodes[0].Value.Split(',').Select(uint.Parse).ToList();

            foreach (uint tileCollisionValue in tileCollisionValues)
            {
                uint tileIndex = tileCollisionValue;

                if ((tileCollisionValue & TILED_FLIPPED_HORIZONTALLY_FLAG) > 0)
                    tileIndex &= ~TILED_FLIPPED_HORIZONTALLY_FLAG;

                if ((tileCollisionValue & TILED_FLIPPED_VERTICALLY_FLAG) > 0)
                    tileIndex &= ~TILED_FLIPPED_VERTICALLY_FLAG;

                var tileIndexes = tileAttributeTileset.TileIndexes.First();

                if (tileIndex >= tileIndexes.StartIndex && tileIndex < tileIndexes.EndIndex)
                {
                    tileIndex -= tileIndexes.StartIndex;
                }
                else
                {
                    tileIndex = 0;
                }

                mCollisionMap.Add(tileIndex);
            }
        }

        public void ExportHeaderFile(ExportMode exportMode)
        {
            // Save to header file
            using (System.IO.StreamWriter headerFile = new System.IO.StreamWriter(mDestinationHeaderFile))
            {
                string headerBlock = MapName.ToUpper() + "_MAP_INCLUDE_H";

                headerFile.WriteLine("// this file was automatically generated by tmx2c. ");
                headerFile.WriteLine("#ifndef " + headerBlock);
                headerFile.WriteLine("#define " + headerBlock);
                headerFile.WriteLine("");
                headerFile.WriteLine("#include \"engine\\map_types.h\""); 
                headerFile.WriteLine("");

                switch (exportMode)
                {
                case ExportMode.Map:
                    headerFile.WriteLine("RESOURCE() extern const Ruby_Map const " + MapName + "_map;");
                break;
                case ExportMode.StripMap:
                    headerFile.WriteLine("RESOURCE() extern const Ruby_StripMap const " + MapName + "_map;");
                break;
                }

                
                

                headerFile.WriteLine("");
                headerFile.WriteLine("#endif");
            }
        }

        private void ExportMapArray(StringBuilder exported, string tilemapArrayName)
        {
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int counter = 0;
            int totalSize = MapWidth * MapHeight;

            exported.Append("// array of metatile indexes. use the metatile look up table to figure out which actual 8x8 tiles to use.\n");
            exported.Append("const unsigned short const " + tilemapArrayName + "[" + totalSize + "] = \n");
            exported.Append("{\n");
            exported.Append("    ");


            for (int loop = 0; loop < totalSize; loop++)
            {
                Tile tile = mTilemap[loop];

                ExportTile(exported, tile, loop);

                counter++;

                if (counter == MapWidth)
                {
                    exported.Append("\n    ");
                    counter = 0;
                }
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        private void ExportStripMapArray(StringBuilder exported, string stripmapArrayName)
        {
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int totalSize = MapWidth * MapHeight;

            exported.Append("const unsigned short const " + stripmapArrayName + "[" + totalSize + "] = // " + MapWidth + " x " + MapHeight + "\n");
            exported.Append("{\n");
            exported.Append("    ");

            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            var tileset = usedTilesets.First();
            uint vdpTileOffset = 448 - tileset.NumTiles;

            for (int widthLoop = 0; widthLoop < MapWidth; widthLoop++)
            {
                for (int heightLoop = 0; heightLoop < MapHeight; heightLoop++)
                {
                    int mapLocation = widthLoop + (heightLoop * MapWidth);

                    Tile tile = mTilemap[mapLocation];

                    ExportTile(exported, tile, mapLocation);
                }

                exported.Append("\n    ");
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        // this has to match the ones in the game engine
        const int TILE_EMPTY = 0;
        const int TILE_SOLID = 1;
        const int TILE_TOPSOLID = 2;
        const int TILE_CLIMB = 3;
        const int TILE_HURT = 4;
        const int TILE_SLOPE45RIGHT = 5;
        const int TILE_SLOPE45LEFT = 6;
        const int TILE_SLOPE30RIGHT1 = 7;
        const int TILE_SLOPE30RIGHT2 = 8;
        const int TILE_SLOPE30LEFT1 = 9;
        const int TILE_SLOPE30LEFT2 = 10;
        const int TILE_WATER = 11;

        private void ExportStripMapTerrain(StringBuilder exported, string terrainMapArrayName)
        {
            
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int totalSize = MapWidth * MapHeight;

            exported.Append("const unsigned char const " + terrainMapArrayName + "[" + totalSize + "] = // " + MapWidth + " x " + MapHeight + "\n");
            exported.Append("{\n");
            exported.Append("    ");

            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);
            var tileset = usedTilesets.First();

            for (int widthLoop = 0; widthLoop < MapWidth; widthLoop++)
            {
                int metaTileRow = widthLoop & 1;

                for (int heightLoop = 0; heightLoop < MapHeight; heightLoop++)
                {
                    int location = widthLoop + (heightLoop * MapWidth);
                    Tile tile = mTilemap[location];

                    uint tileAttribute = TILE_EMPTY;

                    uint tileIndex = tile.Index;

                    tileIndex -= tileset.TileIndexes.First().StartIndex - tileset.ExportStartIndex;

                    tileIndex -= tileset.ExportStartIndex;

                    if (tileIndex > 0)
                    {
                        // if we have a terrain layer, use the data from it.
                        // if not, use the default terrain from the tileset
                        if (mTerrainLayerNode != null)
                        {
                            tileAttribute = mCollisionMap[location];
                        }
                        else
                        {
                            // tile attribute
                            var tileAttributeString = "";

                            if (tileIndex < tileset.TileAttributes.Count())
                            {
                                tileAttributeString = tileset.TileAttributes[tileIndex];
                            }

                            switch (tileAttributeString)
                            {
                                case "solid": tileAttribute = TILE_SOLID; break;
                                case "topsolid": tileAttribute = TILE_TOPSOLID; break;
                                case "climb": tileAttribute = TILE_CLIMB; break;
                                case "hurt": tileAttribute = TILE_HURT; break;
                                case "slope45right": tileAttribute = TILE_SLOPE45RIGHT; break;
                                case "slope45left": tileAttribute = TILE_SLOPE45LEFT; break;
                                case "slope30right1": tileAttribute = TILE_SLOPE30RIGHT1; break;
                                case "slope30right2": tileAttribute = TILE_SLOPE30RIGHT2; break;
                                case "slope30left1": tileAttribute = TILE_SLOPE30LEFT1; break;
                                case "slope30left2": tileAttribute = TILE_SLOPE30LEFT2; break;
                                case "water": tileAttribute = TILE_WATER; break;
                            }
                        }
                    }

                    exported.Append(tileAttribute + ",");
                }

                exported.Append("\n    ");
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }



        private void ExportTile(StringBuilder exported, Tile tile, int mapLocationIndex)
        {
            uint tileAttribute = TILE_EMPTY;
            uint tileIndex = tile.Index;
            uint originalTileIndex = tileIndex;

            /*
            // Don't think the bit format supports flipping now.
            if (tile.HorizontalFlip)
                tileIndex |= GenesisFlippedHorizontallyFlag;

            if (tile.VerticalFlip)
                tileIndex |= GenesisFlippedVerticallyFlag;
                */

            var tileset = tile.Tileset;

            if (tileset == null)
            {
                tileIndex = 0; // leave tiles that come from the game object tileset as blank.
            }
            else
            {
                tileIndex -= tileset.TileIndexes.First().StartIndex - tileset.ExportStartIndex;

                tileIndex -= tileset.ExportStartIndex;

                // exported format of map values
                // tile_type     | blockmap_index | block_index
                // 1111            111              111111111
                // 0 - 15          0 - 7            0 - 511

                // tileset index
                uint tilesetIndex = (tileset.TilesetIndex << 9);

                // if we have a terrain layer, use the data from it.
                // if not, use the default terrain from the tileset
                if (mTerrainLayerNode != null)
                {
                    tileAttribute = mCollisionMap[mapLocationIndex];
                }
                else
                {
                    // tile attribute
                    var tileAttributeString = "";

                    if (tileIndex < tileset.TileAttributes.Count())
                    {
                        tileAttributeString = tileset.TileAttributes[tileIndex];
                    }

                    switch (tileAttributeString)
                    {
                        case "solid": tileAttribute = TILE_SOLID; break;
                        case "topsolid": tileAttribute = TILE_TOPSOLID; break;
                        case "climb": tileAttribute = TILE_CLIMB; break;
                        case "hurt": tileAttribute = TILE_HURT; break;
                        case "slope45right": tileAttribute = TILE_SLOPE45RIGHT; break;
                        case "slope45left": tileAttribute = TILE_SLOPE45LEFT; break;
                        case "slope30right1": tileAttribute = TILE_SLOPE30RIGHT1; break;
                        case "slope30right2": tileAttribute = TILE_SLOPE30RIGHT2; break;
                        case "slope30left1": tileAttribute = TILE_SLOPE30LEFT1; break;
                        case "slope30left2": tileAttribute = TILE_SLOPE30LEFT2; break;
                        case "water": tileAttribute = TILE_WATER; break;
                    }
                }

                tileIndex |= (tileAttribute << 12) | tilesetIndex;

                //tileIndex -= 1;
            }

            exported.Append(tileIndex + ",");
        }
        

        private void ExportTerrainMap(StringBuilder exported, string terrainMapArrayName)
        {
            if (string.IsNullOrEmpty(terrainMapArrayName))
                return;

            exported.Append("\n");

            int counter = 0;
            int totalSize = MapWidth * MapHeight;

            exported.Append("const unsigned short const " + terrainMapArrayName + "[" + totalSize + "] = \n");
            exported.Append("{\n");
            exported.Append("    ");

            for (int loop = 0; loop < totalSize; loop++)
            {
                uint tileIndex = mCollisionMap[loop];

                exported.Append(tileIndex + ",");

                counter++;

                if (counter == MapWidth)
                {
                    exported.Append("\n    ");
                    counter = 0;
                }
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        private void ExportTilesets(StringBuilder exported)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("\n");
            foreach (var tileset in usedTilesets)
            {
                exported.Append("extern const Ruby_Tileset " + tileset.TilesetName + ";\n");
            }
            exported.Append("\n");
        }


        private void ExportTilesetArray(StringBuilder exported)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("\n");
            exported.Append("const Ruby_Tileset* " + MapName + "_tilesets[" + Tilesets.Count + "] = \n");
            exported.Append("{\n");

            foreach (var tileset in usedTilesets)
            {
                exported.Append("    &" + tileset.TilesetName + ", // ");
                exported.Append(tileset.IsAnimated ? "AnimatedTileset" : "Tileset");
                exported.AppendLine();
            }

            exported.Append("};\n");
            exported.Append("\n");
        }

        private void ExportMapStruct(StringBuilder exported, string tilemapArrayName)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("RESOURCE() const Map const " + MapName + "_map = \n");
            exported.Append("{\n");
            exported.AppendLine("    MAP_RESOURCE_TYPE,");
            exported.Append("    " + tilemapArrayName + ", // metatile index map data\n");
            //exported.Append("    " + tilemapArrayName + "_terrain, // terrain\n");
            exported.Append("    " + MapName + "_tilesets, // tilesets used in the map\n");
            exported.Append("    " + usedTilesets.Count() + ", // number of tilesets used by this map\n");
            exported.Append("    " + MapWidth + ", // metatile map width\n");
            exported.Append("    " + MapHeight + ", // metatile map height\n");
            exported.Append("};\n");
            exported.Append("\n");
        }

        private void ExportStripMapStruct(StringBuilder exported, string tilemapArrayName, string terrainMapArrayName)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("RESOURCE() const Ruby_StripMap const " + MapName + "_map = \n");
            exported.Append("{\n");
            exported.AppendLine("    STRIP_MAP_RESOURCE_TYPE,");
            exported.Append("    " + tilemapArrayName + ", // strip map data\n");

            exported.Append("    (const Resource*)&" + usedTilesets.First().TilesetName + ", \n");

            exported.Append("    " + MapWidth + ", // map width\n");
            exported.Append("    " + MapHeight + ", // map height\n");

            exported.Append("    " + terrainMapArrayName + ", // terrain map data\n");
            exported.Append("    " + MapWidth + ", // terrain map width\n");
            exported.Append("    " + MapHeight + ", // terrain map height\n");

            exported.Append("};\n");
            exported.Append("\n");
        }


        public void ExportSourceFile(ExportMode exportMode)
        {
            StringBuilder exported = new StringBuilder();
            ExportInclude(exported);

            // uncomment to debug
            /*
            if (mTerrainLayerNode != null)
            {
                ExportTerrainMap(exported, MapName + "_terrainmap_array");
            }
            */

            ExportMap(exported, exportMode);

            //ExportStripBlockMap(exported);

            using (System.IO.StreamWriter sourceFile = new System.IO.StreamWriter(mDestinationSourceFile))
            {
                sourceFile.Write(exported.ToString());
            }
        }

        private void ExportMap(StringBuilder exported, ExportMode exportMode)
        {
            ExportTilesets(exported);

            if (exportMode == ExportMode.Map)
            {
                ExportTilesetArray(exported);

                string mapArrayName = MapName + "_metatile_map";
                ExportMapArray(exported, mapArrayName);
                ExportMapStruct(exported, mapArrayName);
            }
            else if (exportMode == ExportMode.StripMap)
            {
                ExportStripMap(exported);
            }
        }

        private void ExportStripMap(StringBuilder exported)
        {
            string stripmapArrayName = MapName + "_strip_map";

            ExportStripMapArray(exported, stripmapArrayName);

            string terrainMapArrayName = MapName + "_terrain_map";
            ExportStripMapTerrain(exported, terrainMapArrayName);

            ExportStripMapStruct(exported, stripmapArrayName, terrainMapArrayName);
        }



        private void ExportInclude(StringBuilder exported)
        {
            exported.Append("// this file was automatically generated by tmx2c. \n");
            exported.Append("#include \"" + MapName + ".h\"\n");
            exported.Append("#include \"engine\\resource_types.h\"\n");
        }

        public void Export(ExportMode exportMode)
        {
            ParseTileMapLayer(mTilemapLayerNode);

            if (mTerrainLayerNode != null)
                ParseTerrainLayer(mTerrainLayerNode);

            ExportHeaderFile(exportMode);
            ExportSourceFile(exportMode);
        }
    }
}
