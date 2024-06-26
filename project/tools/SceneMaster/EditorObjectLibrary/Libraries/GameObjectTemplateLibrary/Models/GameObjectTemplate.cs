﻿using PropertyTools.DataAnnotations;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.IO;
using System.Linq;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    public enum GameObjectType
    {
        Undefined = -1,
        Projectile,
        Enemy,
        Effect,
        Player,
        CommandRunner,
        Scroller,
        Item
    }

    public class GameObjectTemplate : EditorObjectInfo
    {
        public GameObjectTemplate() : base(EditorObjectType.GameObject)
        {
        }

        [System.ComponentModel.ReadOnly(true)]
        public string FilePath { get; private set; }

        [System.ComponentModel.ReadOnly(true)]
        public bool IsUnique { get; private set; } = false;

        // game properties
        [System.ComponentModel.ReadOnly(true)]
        public int Health { get; set; }

        [System.ComponentModel.ReadOnly(true)]
        public int RectLeft { get; set; } = 0;

        [System.ComponentModel.ReadOnly(true)]
        public int RectTop { get; set; } = 0;

        [System.ComponentModel.ReadOnly(true)]
        public int RectRight { get; set; } = 0;

        [System.ComponentModel.ReadOnly(true)]
        public int RectBottom { get; set; } = 0;

        [System.ComponentModel.ReadOnly(true)]
        [SelectorStyle(SelectorStyle.ComboBox)]
        public GameObjectType GameObjectType { get; set; }

        [System.ComponentModel.ReadOnly(true)]
        public string InitFunction { get; set; }

        [System.ComponentModel.ReadOnly(true)]
        public string CreateInfoType { get; set; }

        public void LoadEditorProperties(XmlElement editorPropertiesNode)
        {
            if (editorPropertiesNode["Visual"] is var visualNode && visualNode != null)
            {
                Visual.Load(visualNode);
            }
        }

        public void LoadGameProperties(XmlElement gamePropertiesNode)
        {
            Health = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(Health));
            GameObjectType = XmlUtils.GetChildValue<GameObjectType>(gamePropertiesNode, nameof(GameObjectType));
            RectLeft = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(RectLeft));
            RectTop = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(RectTop));
            RectRight = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(RectRight));
            RectBottom = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(RectBottom));
            Resource = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Resource));
            InitFunction = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(InitFunction));
            CreateInfoType = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(CreateInfoType));

            GameObjectType = XmlUtils.GetChildValue<GameObjectType>(gamePropertiesNode, nameof(GameObjectType));

            IsUnique = XmlUtils.HasChild(gamePropertiesNode, nameof(IsUnique));

            if (string.IsNullOrEmpty(InitFunction))
                throw new Exception("No init function in object template.");
        }

        public void Load(string filePath)
        {
            FilePath = filePath;

            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            string oldCurrentDirectory = Directory.GetCurrentDirectory();

            Directory.SetCurrentDirectory(Path.GetDirectoryName(filePath));

            try
            {

                LoadContents(root);
            }
            finally 
            {
                Directory.SetCurrentDirectory(oldCurrentDirectory);
            }
        }

        protected override void LoadContents(XmlElement root)
        {
            base.LoadContents(root);

            Name = "UnnamedGameObjectTemplate";
            if (root[nameof(Name)] is var nameNode && nameNode != null)
            {
                Name = nameNode.Attributes["value"]?.Value ?? "UnnamedGameObjectTemplate";
            }

            if (root["EditorProperties"] is var editorPropertiesNode && editorPropertiesNode != null)
            {
                IsEditorVisible = true;
                LoadEditorProperties(editorPropertiesNode);
            }

            if (root["GameProperties"] is var gamePropertiesNode && gamePropertiesNode != null) 
            {
                LoadGameProperties(gamePropertiesNode);
            }
        }

        internal override EditorObject CreateEditorObject(int x, int y, Scene scene)
        {
            if (IsUnique && scene.EditorObjects.FirstOrDefault(e => e is GameObject g && g.GameObjectTemplate == this) != null)
            { 
                return null; 
            }

            return new GameObject(x, y, Name, this);
        }
    }
}
