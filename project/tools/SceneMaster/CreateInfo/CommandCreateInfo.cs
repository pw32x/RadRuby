using PropertyTools.DataAnnotations;
using SceneMaster.Utils;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace SceneMaster.CreateInfoTypes
{

    public class DrawMapCommandData : BaseCreateInfo
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

	    private byte m_x;		// where in the plane to draw
        public byte X
        {
            get => m_x; 
            set { m_x = value; OnPropertyChanged(); }
        }


	    private byte m_y;		// where in the plane to draw
        public byte Y
        {
            get => m_y; 
            set { m_y = value; OnPropertyChanged(); }
        }

	    private byte m_mapx;	// tile map source x
        public byte MapX
        {
            get => m_mapx;
            set { m_mapx = value; OnPropertyChanged(); }
        }

	    private byte m_mapy;	// tile map source y
        public byte MapY
        {
            get => m_mapy;
            set { m_mapy = value; OnPropertyChanged(); }
        }

	    private byte m_width;	// the width of the map section to draw
        public byte Width
        {
            get => m_width; 
            set { m_width = value;  OnPropertyChanged(); }
        }

	    private byte m_height;  // the height of the map section to draw
        public byte Height
        {
            get => m_height;
            set { m_height = value; OnPropertyChanged(); } 
        }

        private string MapName => Path.GetFileNameWithoutExtension(MapResource) + "_map";

        public override void Export(StringBuilder sb)
        {
            sb.Append((string.IsNullOrEmpty(MapResource) ? "NULL" : "&" + MapName) +
                      ", " + m_x +
                      ", " + m_y +
                      ", " + m_mapx +
                      ", " + m_mapy +
                      ", " + m_width +
                      ", " + m_height);
        }

        public override void ExportContentsToXmlNode(XmlElement node)
        {
            node.SetAttribute(nameof(MapResource), MapResource);
            node.SetAttribute(nameof(X), X.ToString());
            node.SetAttribute(nameof(Y), Y.ToString());
            node.SetAttribute(nameof(MapX), MapX.ToString());
            node.SetAttribute(nameof(MapY), MapY.ToString());
            node.SetAttribute(nameof(Width), Width.ToString());
            node.SetAttribute(nameof(Height), Height.ToString());
        }

        internal override void ReadFromXml(XmlElement createInfoNode)
        {
            MapResource = XmlUtils.GetValue<string>(createInfoNode, nameof(MapResource));
            X = XmlUtils.GetValue<byte>(createInfoNode, nameof(X));
            Y = XmlUtils.GetValue<byte>(createInfoNode, nameof(Y));
            MapX =  XmlUtils.GetValue<byte>(createInfoNode, nameof(MapX));
            MapY = XmlUtils.GetValue<byte>(createInfoNode, nameof(MapY));
            Width =  XmlUtils.GetValue<byte>(createInfoNode, nameof(Width));
            Height = XmlUtils.GetValue<byte>(createInfoNode, nameof(Height));
        }

        internal override IEnumerable<string> Resources()
        {
            yield return MapName;
            
            foreach (var resource in base.Resources())
                yield return resource;
        }
    }

}