using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.Utils;
using System.Text;
using System.Xml;

namespace SceneMaster.CreateInfoTypes
{
    public abstract class BaseCreateInfo : ObservableObject
    {
        public abstract void Export(StringBuilder sb);

        public void SaveToXml(XmlElement parentNode, XmlDocument doc)
        {
            var newNode = doc.CreateElement(GetType().Name);

            ExportContentsToXmlNode(newNode);

            parentNode.AppendChild(newNode);
        }

        public abstract void ExportContentsToXmlNode(XmlElement node);

        internal abstract void ReadFromXml(XmlElement createInfoNode);
    }

    public class CreateInfo : BaseCreateInfo
    {
        private sbyte m_speedX;
        public sbyte SpeedX 
        { 
            get => m_speedX;
            set
            {
                m_speedX = value;
                OnPropertyChanged();
            }
        }

        private sbyte m_speedY;
        public sbyte SpeedY 
        { 
            get => m_speedY;
            set
            {
                m_speedY = value;
                OnPropertyChanged();
            }
        }

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + SpeedX + ", " + SpeedY);
        }

        public override void ExportContentsToXmlNode(XmlElement node)
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
        private byte m_startFrameNumber;
        public byte StartFrameNumber 
        { 
            get => m_startFrameNumber;
            set
            {
                m_startFrameNumber = value;
                OnPropertyChanged();
            }
        }

        public override void Export(StringBuilder sb)
        {
            base.Export(sb);
            sb.Append(", " + StartFrameNumber);
        }

        public override void ExportContentsToXmlNode(XmlElement node)
        {
            base.ExportContentsToXmlNode(node);
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
        private string m_commands = "NULL";
        public string Commands 
        { 
            get => m_commands;
            set
            {
                m_commands = value;
                OnPropertyChanged();
            }
        }

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + (string.IsNullOrEmpty(Commands) ? "NULL" : "&" + Commands));
        }

        public override void ExportContentsToXmlNode(XmlElement node)
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
        private string m_mapResource = "NULL";
        public string MapResource 
        { 
            get => m_mapResource;
            set
            {
                m_mapResource = value;
                OnPropertyChanged();
            }
        }

        public override void Export(StringBuilder sb)
        {
            sb.Append(", " + (string.IsNullOrEmpty(MapResource) ? "NULL" : "&" + MapResource));
        }

        public override void ExportContentsToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(MapResource), MapResource);
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            MapResource = XmlUtils.GetValue<string>(createInfoNode, nameof(MapResource));
        }
    }
}