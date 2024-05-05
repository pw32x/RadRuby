using SceneMaster.CreateInfoTypes;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    public class GameObject : EditorObject
    {
        public GameObject(int x, 
                          int y, 
                          string name, 
                          GameObjectTemplate gameObjectTemplate) : base(x, y, name, gameObjectTemplate)
        {
            CreateCreateInfo(gameObjectTemplate.CreateInfoType);
        }

        public BaseCreateInfo CreateInfo { get; set; }

        public GameObject(XmlElement gameObjectNode, 
                          GameObjectTemplateLibrary gameObjectTemplateLibrary) : base(gameObjectNode)
        {
            string gameObjectTemplateName = XmlUtils.GetValue<string>(gameObjectNode, nameof(GameObject.GameObjectTemplateName));

            if (!gameObjectTemplateLibrary.GameObjectTemplates.TryGetValue(gameObjectTemplateName, out var gameObjectTemplate))
            {
                gameObjectTemplate = gameObjectTemplateLibrary.DefaultGameObjectTemplate;
            }

            CreateCreateInfo(gameObjectTemplate.CreateInfoType);

            if (gameObjectNode[CreateInfo.GetType().Name] is var createInfoNode && createInfoNode != null) 
            {
                CreateInfo.ReadFromXml(createInfoNode);
            }

            EditorObjectInfo = gameObjectTemplate;
        }

        private void CreateCreateInfo(string createInfoTypeName)
        {
            // use the TypeName to create the object dynamically through reflection
            switch (createInfoTypeName)
            {
            /*
            case nameof(EffectCreateInfo):
                CreateInfo = new EffectCreateInfo();
                break;
                */
            case nameof(CommandRunnerCreateInfo):
                CreateInfo = new CommandRunnerCreateInfo();
                break;
            case nameof(ScrollerCreateInfo):
                CreateInfo = new ScrollerCreateInfo();
                break;
            default:
                CreateInfo = new CreateInfo();
                break;
            }
        }

        public string GameObjectTemplateName => GameObjectTemplate.Name;
        public GameObjectTemplate GameObjectTemplate => EditorObjectInfo as GameObjectTemplate;

        internal override ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int exportCounter)
        {
            string createInfoName = sceneName + "_createInfo_" + GameObjectTemplate.Name.Replace(" ", "") + exportCounter;

            var exportedCommandData = new ExportedCommandData();
            exportedCommandData.CreateInfoTypeName = createInfoName;

            StringBuilder sb = new();
            sb.Append("const " + CreateInfo.GetType().Name + " " + createInfoName + " = { ");
            string templateName = Path.GetFileNameWithoutExtension(GameObjectTemplate.FilePath) + "_template";

            int x;
            int y;

            if (SpawnPointIsIndependant)
            {
                x = (int)(SpawnX < 0 ? 0 : SpawnX);
                y = (int)(SpawnY < 0 ? 0 : SpawnY);
            }
            else
            {
                x = (int)(X < 0 ? 0 : X);
                y = (int)(Y < 0 ? 0 : Y);
            }

            x += GameObjectTemplate.Visual?.OffsetX ?? 0;
            y += GameObjectTemplate.Visual?.OffsetY ?? 0;


            sb.Append("&" + templateName + ", " + x + ", " + y);

            CreateInfo.Export(sb);

            sb.AppendLine(" };");
            exportedCommandData.ExportedCreateInfo = sb.ToString();
            exportedCommandData.CommandToUse = "ObjectManager_CreateObjectByCreateInfo";
            return exportedCommandData;

            /*
            case GameObjectTemplates.Models.EditorObjectType.Palette:
            {
                var exportedCommandData = new ExportedCommandData();
                exportedCommandData.ExportedCreateInfo = "";
                exportedCommandData.CreateInfoTypeName = "";
                exportedCommandData.CommandToUse = gameObject.GameObjectTemplate.InitFunction;
                exportedCommandDatas.Add(gameObject, exportedCommandData);
                break;
            }
            */
        }

        internal override string BuildSceneCommand(ExportedCommandData exportedCommandData)
        {
            // clamp to 0
            int x = (int)(X < 0 ? 0 : X);

            // only works for the right scroller for now:
            // offset the spawn offset by the rect right of the object so that it'll
            // pop appear on screen. Becaues SMS has no clipping, the sprite will appear
            // half on each side of the screen, which we want to avoid.
            x += GameObjectTemplate.RectRight + GameObjectTemplate.Visual.OffsetX;

            string finalExportedCommandData = "NULL";
            if (!string.IsNullOrEmpty(exportedCommandData.CreateInfoTypeName))
            {
                finalExportedCommandData = "&" + exportedCommandData.CreateInfoTypeName;

                //if (GameObjectTemplate.GameObjectType == GameObjectType.CommandRunner)
                //{
                //    finalExportedCommandData = "(const CreateInfo*)" + finalExportedCommandData;
                //}
            }

            return "{ " + x + ", (CommandFunction)" + exportedCommandData.CommandToUse + ", " + finalExportedCommandData + " },";
        }

        internal override XmlElement SaveToXml(XmlDocument doc)
        {
            var newNode = base.SaveToXml(doc);
            newNode.SetAttribute(nameof(GameObjectTemplateName), GameObjectTemplateName);

            CreateInfo.SaveToXml(newNode, doc);

            return newNode;
        }

        public override IEnumerable<string> Resources()
        {
            foreach (var resource in base.Resources())
                yield return resource;

            foreach (var resource in CreateInfo.Resources())
                yield return resource;
        }
    }
}