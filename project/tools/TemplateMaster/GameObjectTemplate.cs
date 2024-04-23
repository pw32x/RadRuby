using TemplateMaster.Utils;
using System.Xml;

namespace TemplateMaster
{
    public class GameObjectTemplate
    {
        public string Name { get; set; } = "";
        public string Health { get; set; } = "0";
        public string Damage { get; set; } = "0";
        public string RectLeft { get; set; } = "0";
        public string RectTop { get; set; } = "0";
        public string RectRight { get; set; } = "0";
        public string RectBottom { get; set; } = "0";
        public string GameObjectType { get; set; } = "";
        public string Resource { get; set; } = "";
        public string InitFunction { get; set; } = "";
        public List<string> ExtraResources { get; set; } = new List<string>();
        public List<string> CustomDataFields { get; set; } = new List<string>();

        public void LoadGameProperties(XmlElement gamePropertiesNode)
        {
            Health = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Health));
            Damage = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Damage));

            RectLeft = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectLeft));
            RectTop = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectTop));
            RectRight = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectRight));
            RectBottom = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectBottom));

            GameObjectType = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(GameObjectType));
            Resource = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Resource));
            InitFunction = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(InitFunction));

            if (gamePropertiesNode["ExtraResources"] is var extraResourcesNode && extraResourcesNode != null) 
            {
                foreach (var extraResourceNode in extraResourcesNode.ChildNodes.OfType<XmlElement>())
                {
                    string nodeType = extraResourceNode.Name;

                    if (nodeType != "Resource")
                        continue;

                    var value = XmlUtils.GetValue<string>(extraResourceNode);

                    if (string.IsNullOrEmpty(value))
                        continue;

                    ExtraResources.Add(value);
                }
            }

            if (gamePropertiesNode["CustomData"] is var customDataNode && customDataNode != null)
            {
                foreach (var dataNode in customDataNode.ChildNodes.OfType<XmlElement>())
                {
                     string nodeType = dataNode.Name;

                    if (nodeType != "Data")
                        continue;

                    var value = XmlUtils.GetValue<string>(dataNode);

                    if (string.IsNullOrEmpty(value))
                        continue;

                    CustomDataFields.Add(value);
                }
            }
        }

        public void Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            if (root[nameof(Name)] is var nameNode && nameNode != null)
            {
                Name = nameNode.Attributes["value"]?.Value ?? "UnnamedGameObjectTemplate";
            }

            if (root["GameProperties"] is var gamePropertiesNode && gamePropertiesNode != null) 
            {
                LoadGameProperties(gamePropertiesNode);
            }
        }
    }
}
