
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

    public class Scene : ObservableObject
    {
        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();

        [Browsable(false)]
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        public string ForegroundMapPath { get; set; }
        public string BackgroundMapPath { get; set; }

        // replace with guids
        public string ForegroundMapScrollerName { get; set; }
        public string BackgroundMapScrollerName { get; set; }

        private const string ForegroundTiledMapFilePathNodeName = "ForegroundTiledMapFilePath";
        private const string BackgroundTiledMapFilePathNodeName = "BackgroundTiledMapFilePath";
        private const string ForegroundTiledMapScrollerNodeName = "ForegroundTiledMapScrollerName";
        private const string BackgroundTiledMapScrollerNodeName = "BackgroundTiledMapScrollerName";
        private const string EditorObjectsNodeName = "EditorObjects";
        //private const string TerrainNodeName = "Terrain";

        public Scene(/*List<BitmapImage> tileTypeImages*/)
        {
            //m_tileTypeImages = tileTypeImages;
        }

        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var foregroundFilePathNode = root[ForegroundTiledMapFilePathNodeName];
            if (foregroundFilePathNode != null && !string.IsNullOrEmpty(foregroundFilePathNode.InnerText))
            {
                ForegroundMapPath = Path.Combine(Path.GetDirectoryName(filePath), foregroundFilePathNode.InnerText);
                
            }

            var backgroundFilePathNode = root[BackgroundTiledMapFilePathNodeName];
            if (backgroundFilePathNode != null && !string.IsNullOrEmpty(backgroundFilePathNode.InnerText))
            {
                BackgroundMapPath = Path.Combine(Path.GetDirectoryName(filePath), backgroundFilePathNode.InnerText);
            }

            var foregroundTiledMapScrollerNodeName = root[ForegroundTiledMapScrollerNodeName];
            if (foregroundTiledMapScrollerNodeName != null)
            {
                ForegroundMapScrollerName  = foregroundTiledMapScrollerNodeName.InnerText;
            }

            var backgroundTiledMapScrollerNodeName = root[BackgroundTiledMapScrollerNodeName];
            if (backgroundTiledMapScrollerNodeName != null)
            {
                BackgroundMapScrollerName  = backgroundTiledMapScrollerNodeName.InnerText;
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
            foregroundFilePathNode.InnerText = string.IsNullOrEmpty(ForegroundMapPath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), ForegroundMapPath);
            root.AppendChild(foregroundFilePathNode);

            // background tiled map file path
            var backgroundFilePathNode = doc.CreateElement(BackgroundTiledMapFilePathNodeName);
            backgroundFilePathNode.InnerText = string.IsNullOrEmpty(BackgroundMapPath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), BackgroundMapPath);
            root.AppendChild(backgroundFilePathNode);

            // foreground scroller name
            var foregroundTiledMapScrollerNode = doc.CreateElement(ForegroundTiledMapScrollerNodeName);
            foregroundTiledMapScrollerNode.InnerText = string.IsNullOrEmpty(ForegroundMapScrollerName) ? "" : ForegroundMapScrollerName;
            root.AppendChild(foregroundTiledMapScrollerNode);

            // background scroller name
            var backgroundTiledMapScrollerNode = doc.CreateElement(BackgroundTiledMapScrollerNodeName);
            backgroundTiledMapScrollerNode.InnerText = string.IsNullOrEmpty(BackgroundMapScrollerName) ? "" : BackgroundMapScrollerName;
            root.AppendChild(backgroundTiledMapScrollerNode);

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


    }
}