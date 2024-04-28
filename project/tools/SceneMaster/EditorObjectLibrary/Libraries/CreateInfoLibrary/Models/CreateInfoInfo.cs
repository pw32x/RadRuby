using System.Collections.Generic;

namespace SceneMaster.CreateInfo.Models
{
    public class CreateInfoField
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string DefaultValue { get; set; }
    }

    public class CreateInfoInfo
    {
        public string Name { get; set; }
        public List<CreateInfoField> Fields { get; set; } = new();
        public string Filename { get; internal set; }
    }
}