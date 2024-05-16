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
        public string CreateInfoDataName { get; set; }
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
            Guid = Guid.NewGuid();
        }

        public virtual object ObjectData { get; } = null;

        public EditorObject(XmlElement node)
        {
            X = XmlUtils.GetValue<int>(node, nameof(X));
            Y = XmlUtils.GetValue<int>(node, nameof(Y));
            SpawnX = XmlUtils.GetValue<int>(node, nameof(SpawnX), X);
            SpawnY = XmlUtils.GetValue<int>(node, nameof(SpawnY), Y);
            SpawnPointIsIndependant = XmlUtils.GetValue<bool>(node, nameof(SpawnPointIsIndependant), false);
            Name = XmlUtils.GetValue<string>(node, nameof(Name));

            string attributeValue = node.Attributes[nameof(Guid)]?.Value ?? "";
            if (!string.IsNullOrEmpty(attributeValue))
            {
                Guid.TryParse(attributeValue, out var guid);
                Guid = guid;
            }

            if (Guid == Guid.Empty)
                Guid = Guid.NewGuid();
        }

        public int X { get; set; }
        public int Y { get; set; }

        public int SpawnX { get; set; }
        public int SpawnY { get; set; }

        public string Name { get; set; }
        public Guid Guid { get; set; }
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
            newNode.SetAttribute(nameof(Guid), Guid.ToString());
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