using CommunityToolkit.Mvvm.ComponentModel;
using PropertyTools.DataAnnotations;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.Interfaces;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.Xml;

namespace SceneMaster.EditorObjects.Models
{
    public class ExportedCommandData
    {
        public string CreateInfoTypeName { get; set; }
        public string ExportedCreateInfo { get; set; }
        public string CommandToUse { get; set; }
    }

    abstract public class EditorObject
    {
        public EditorObject(int x, 
                            int y, 
                            string name, 
                            EditorObjectInfo editorObjectInfo)
        {
            X = x;
            Y = y;
            Name = name;
            EditorObjectInfo = editorObjectInfo;
        }

        public EditorObject(XmlElement commandObjectNode)
        {
            X = XmlUtils.GetValue<int>(commandObjectNode, nameof(X));
            Y = XmlUtils.GetValue<int>(commandObjectNode, nameof(Y));
            SpawnX = XmlUtils.GetValue<int>(commandObjectNode, nameof(SpawnX), X);
            SpawnY = XmlUtils.GetValue<int>(commandObjectNode, nameof(SpawnY), Y);
            SpawnPointIsIndependant = XmlUtils.GetValue<bool>(commandObjectNode, nameof(SpawnPointIsIndependant), false);
            Name = XmlUtils.GetValue<string>(commandObjectNode, nameof(Name));
        }

        public int X { get; set; }
        public int Y { get; set; }

        public int SpawnX { get; set; }
        public int SpawnY { get; set; }

        public string Name { get; private set; }
        public EditorObjectType EditorObjectType => EditorObjectInfo.EditorObjectType;
        public EditorObjectInfo EditorObjectInfo { get; protected set; }
        public bool SpawnPointIsIndependant { get; internal set; }

        abstract internal ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int exportCounter);
        internal abstract string BuildSceneCommand(ExportedCommandData exportedCommandData);

        internal virtual XmlElement SaveToXml(XmlDocument doc)
        {
            var newNode = doc.CreateElement(EditorObjectType.ToString());

            newNode.SetAttribute(nameof(Name), Name);
            newNode.SetAttribute(nameof(X), X.ToString());
            newNode.SetAttribute(nameof(Y), Y.ToString());
            newNode.SetAttribute(nameof(SpawnX), SpawnX.ToString());
            newNode.SetAttribute(nameof(SpawnY), SpawnY.ToString());
            newNode.SetAttribute(nameof(SpawnPointIsIndependant), SpawnPointIsIndependant.ToString());
            return newNode;
        }

        
        virtual public IEnumerable<string> Resources()
        {
            foreach (var resource in EditorObjectInfo.Resources())
                yield return resource;
        }
    }
}