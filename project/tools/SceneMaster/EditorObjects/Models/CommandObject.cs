using PropertyTools.DataAnnotations;
using SceneMaster.CreateInfoTypes;
using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Utils;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace SceneMaster.Commands.Models
{
    public class CommandObject : EditorObject
    {
        public CommandObject(int x, 
                             int y, 
                             string name, 
                             CommandInfo commandInfo) : base(x, y, name, commandInfo)
        {
            CreateCreateInfo(CommandInfo.ParameterTypeName);
        }


        public BaseCreateInfo CreateInfo { get; set; }

        public override object ObjectData { get => CreateInfo; }

        public string m_commandValue = "";

        [VisibleBy("HasNoObjectData")]
        public string CommandValue { get => m_commandValue; set => m_commandValue = value; }

        public string m_preCommandData = ""; // declares a struct or anything before the list of commands in the exported scene

        [VisibleBy("HasNoObjectData")]
        public string PreCommandData { get => m_preCommandData; set => m_preCommandData = value; }

        public string CommandName => CommandInfo.Name;
        public CommandInfo CommandInfo => EditorObjectInfo as CommandInfo;

        public CommandObject(XmlElement commandObjectNode, 
                             CommandLibrary commandLibrary) : base(commandObjectNode)
        {
            string commandInfoName = XmlUtils.GetValue<string>(commandObjectNode, nameof(CommandInfo.Name));

            if (!commandLibrary.CommandInfos.TryGetValue(commandInfoName, out var commandInfo))
                throw new System.Exception("No command info for \"" + commandInfoName + " found.");

            CommandValue = XmlUtils.GetValue<string>(commandObjectNode, nameof(CommandValue));
            PreCommandData = XmlUtils.GetValue<string>(commandObjectNode, nameof(PreCommandData));

            EditorObjectInfo = commandInfo;

            CreateCreateInfo(CommandInfo.ParameterTypeName);

            if (CreateInfo != null && commandObjectNode[CreateInfo.GetType().Name] is var createInfoNode && createInfoNode != null) 
            {
                CreateInfo.ReadFromXml(createInfoNode);
            }
        }

        private void CreateCreateInfo(string createInfoTypeName)
        {
            switch (createInfoTypeName)
            {
                case "DrawMapInfo":
                    CreateInfo = new DrawMapCommandData();
                    break;
            }
        }

        internal override ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int exportCounter)
        {
            var exportedCommandData = new ExportedCommandData();

            if (CreateInfo != null)
            {
                string createInfoName = sceneName + "_createInfo_" + CommandInfo.Name.Replace(" ", "") + exportCounter;

                exportedCommandData.CreateInfoDataName = createInfoName;

                StringBuilder sb = new();

                sb.Append("const " + CreateInfo.GetType().Name + " " + createInfoName + " = { ");
                CreateInfo.Export(sb);
                sb.AppendLine(" };");

                exportedCommandData.ExportedCreateInfo = sb.ToString();
                //exportedCommandData.CommandToUse = "ObjectManager_CreateObjectByCreateInfo";
            }

            return exportedCommandData;

        }

        internal override string BuildSceneCommand(ExportedCommandData exportedCommandData)
        {
            // clamp to 0
            int x = (X < 0 ? 0 : X);

            if (CreateInfo == null)
            {
                string commandValue = CommandValue.StartsWith("&") ? CommandValue : "(const void*)" + CommandValue;
                return "{ " + x + ", (CommandFunction)" + CommandInfo.Name.Replace(" ", "") + ", " + commandValue + " },";
            }
            else
            {
                return "{ " + x + ", (CommandFunction)" + CommandInfo.Name.Replace(" ", "") + ", &" + exportedCommandData.CreateInfoDataName + " },";
            }
        }


        internal override XmlElement SaveToXml(XmlDocument doc)
        {
            var newNode = base.SaveToXml(doc);
            newNode.SetAttribute(nameof(CommandInfo.Name), CommandInfo.Name);

            if (CreateInfo != null)
            {
                CreateInfo.SaveToXml(newNode, doc);
            }
            else
            {
                newNode.SetAttribute(nameof(CommandValue), CommandValue);
                newNode.SetAttribute(nameof(PreCommandData), PreCommandData);
            }

            return newNode;
        }

        public override IEnumerable<string> Resources()
        {
            foreach (var resource in base.Resources())
                yield return resource;

            if (CreateInfo != null)
            {
                foreach (var resource in CreateInfo.Resources())
                    yield return resource;
            }
        }
    }
}