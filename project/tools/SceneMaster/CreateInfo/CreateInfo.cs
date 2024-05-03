using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.Utils;
using System.Text;
using System.Xml;

namespace SceneMaster.CreateInfoTypes
{
    public abstract class BaseCreateInfo
    {
        public abstract void Export(StringBuilder sb);

        public void ExportToXml(XmlElement parentNode, XmlDocument doc)
        {
            var newNode = doc.CreateElement(GetType().Name);

            ExportToXmlNode(newNode);

            parentNode.AppendChild(newNode);
        }

        public abstract void ExportToXmlNode(XmlElement node);
        internal abstract void ReadFromXml(XmlElement createInfoNode);
    }

    public class CreateInfo : BaseCreateInfo
    {
        public sbyte SpeedX { get; set; }
        public sbyte SpeedY { get; set; }

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + SpeedX + ", " + SpeedY);
        }

        public override void ExportToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(SpeedX), SpeedX.ToString());
            node.SetAttribute(nameof(SpeedY), SpeedY.ToString());
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            SpeedX = XmlUtils.GetValue<sbyte>(createInfoNode, nameof(SpeedX));
            SpeedY = XmlUtils.GetValue<sbyte>(createInfoNode, nameof(SpeedY));
        }
    }

    public class EffectCreateInfo : CreateInfo
    {
        public byte StartFrameNumber { get; set; }

        public override void Export(StringBuilder sb)
        {
            base.Export(sb);
            sb.Append(", " + StartFrameNumber);
        }

        public override void ExportToXmlNode(XmlElement node)
        {
            base.ExportToXmlNode(node);
            node.SetAttribute(nameof(StartFrameNumber), StartFrameNumber.ToString());
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            base.ReadFromXml(createInfoNode);
            StartFrameNumber = XmlUtils.GetValue<byte>(createInfoNode, nameof(StartFrameNumber));
        }
    }

    public class CommandRunnerCreateInfo : BaseCreateInfo
    {
        public string Commands { get; set; } = "NULL";

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + (string.IsNullOrEmpty(Commands) ? "NULL" : "&" + Commands));
        }

        public override void ExportToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(Commands), Commands);
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            Commands = XmlUtils.GetValue<string>(createInfoNode, nameof(Commands));
        }
    }

    public class ScrollerCreateInfo : BaseCreateInfo
    {
        public string MapResource { get; set; } = "NULL";

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + (string.IsNullOrEmpty(MapResource) ? "NULL" : "&" + MapResource));
        }

        public override void ExportToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(MapResource), MapResource);
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            MapResource = XmlUtils.GetValue<string>(createInfoNode, nameof(MapResource));
        }
    }
}