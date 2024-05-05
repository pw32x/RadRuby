
using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Xml;

namespace SceneMaster.Scenes.Models
{

    public class Scene : ObservableObject, IDisposable
    {
        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        public TiledMapWrapper TiledMapWrapper { get; } = new();

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";
        //private const string TerrainNodeName = "Terrain";

        public Scene(/*List<BitmapImage> tileTypeImages*/)
        {
            //m_tileTypeImages = tileTypeImages;
        }



        public void ImportTiledMap(string tiledMapFilePath)
        {
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            TiledMapWrapper.LoadTiledMap(tiledMapFilePath);
            //BuildTerrain();
        }


        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                string tiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                TiledMapWrapper.LoadTiledMap(tiledMapFilePath);
                //BuildTerrain();
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
            // tiled map file path
            var ggFilePathNode = doc.CreateElement(TiledMapFilePathNodeName);
            ggFilePathNode.InnerText = string.IsNullOrEmpty(TiledMapWrapper.TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), TiledMapWrapper.TiledMapFilePath);
            root.AppendChild(ggFilePathNode);

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
            TiledMapWrapper.StopWatchingTiledMap();
        }
    }
}