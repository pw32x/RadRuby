using CommunityToolkit.Mvvm.ComponentModel;
using PropertyTools.DataAnnotations;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.IO;
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

        internal virtual IEnumerable<string> Resources()
        {
            yield break;
        }
    }

    public class CreateInfo : BaseCreateInfo
    {
        public override void Export(StringBuilder sb)
        {
        }

        public override void ExportContentsToXmlNode(XmlElement node)
        {
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
        }
    }

    /*
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
    */

    public class CommandRunnerCreateInfo : BaseCreateInfo
    {
        private string m_commands = "";
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
        private string m_mapResource = "";

        [InputFilePath(".tmx", "Tmx files|*.tmx;")]
        public string MapResource 
        { 
            get => m_mapResource;
            set
            {
                m_mapResource = value;
                OnPropertyChanged();
            }
        }

        public enum Plane
        {
            A,
            B
        };

        private Plane m_backgroundPlane = Plane.A;
        public Plane BackgroundPlane
        {
            get => m_backgroundPlane;
            set
            {
                m_backgroundPlane = value;
                OnPropertyChanged();
            }
        }

        private string MapName => Path.GetFileNameWithoutExtension(MapResource) + "_map";

        public override void Export(StringBuilder sb)
        {
            string planeToUse = "BG_A";
            if (m_backgroundPlane == Plane.B)
                planeToUse = "BG_B";

            sb.Append(", " + 
                     (string.IsNullOrEmpty(MapResource) ? "NULL" : "&" + MapName) +
                     ", " + planeToUse);
        }

        public override void ExportContentsToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(MapResource), MapResource);
            node.SetAttribute(nameof(BackgroundPlane), BackgroundPlane.ToString());
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            MapResource = XmlUtils.GetValue<string>(createInfoNode, nameof(MapResource));

            string backgroundPlaneString = XmlUtils.GetValue<string>(createInfoNode, nameof(BackgroundPlane));

            if (Enum.TryParse(typeof(Plane), backgroundPlaneString, true, out var backgroundPlane))
                BackgroundPlane = (Plane)backgroundPlane;
        }

        internal override IEnumerable<string> Resources()
        {
            yield return MapName;
            
            foreach (var resource in base.Resources())
                yield return resource;
        }
    }
}