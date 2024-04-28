using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace SceneMaster.CreateInfo.Models
{
    public class CreateInfoLibrary
    {
        private string m_createInfoSourceDirectory;

        private Dictionary<string, CreateInfoInfo> m_createInfoInfos = new();
        public Dictionary<string, CreateInfoInfo> CreateInfoInfos => m_createInfoInfos;

        private Dictionary<string, CreateInfoInfo> m_failedCreateInfoInfos = new();
        public Dictionary<string, CreateInfoInfo> FailedCreateInfoInfos => m_failedCreateInfoInfos;

        internal void Load(string sourceDirectory)
        {
            m_createInfoSourceDirectory = sourceDirectory;

            var filenames = Directory.GetFiles(m_createInfoSourceDirectory, "*.*", SearchOption.AllDirectories)
                                           .Where(s => s.EndsWith(".h", StringComparison.OrdinalIgnoreCase));


            foreach (var filename in filenames)
            {
                FindCreateInfos(filename);
            }
        }

        private void FindCreateInfos(string filename)
        {
            string[] lines = File.ReadAllLines(filename);

            CreateInfoInfo createInfoInfo = null;

            foreach (var line in lines)
            {
                string contents = line.Trim();

                if (createInfoInfo == null)
                {
                    if (contents.StartsWith("DECLARE_CREATE_INFO("))
                    {
                        createInfoInfo = new CreateInfoInfo();
                    }
                }
                else
                {
                    if (contents.StartsWith("DEC_FIELD("))
                    {
                        int start = contents.LastIndexOf("(");
                        int end = contents.IndexOf(')', start);

                        start++;

                        string info = contents.Substring(start, end - start);
                        var tokens = info.Split(',');

                        var field = new CreateInfoField();
                        field.Type = tokens[0].Trim();
                        field.Name = tokens[1].Trim();
                        field.DefaultValue = tokens[2].Trim();
                        createInfoInfo.Fields.Add(field);
                    }
                    else if (contents.StartsWith("END_CREATE_INFO("))
                    {
                        int start = contents.IndexOf("(");
                        int end = contents.IndexOf(')', start);
                        start++;

                        string name = contents.Substring(start, end - start);

                        createInfoInfo.Name = name;


                        string prettyFilename = "";

                        int index = filename.IndexOf("engine");
                        if (index != -1)
                        {
                            prettyFilename = filename.Substring(index);
                        }
                        else
                        {
                            index = filename.IndexOf("client");

                            // the file isn't in either engine or client, so bail
                            if (index == -1)
                                return;

                            prettyFilename = filename.Substring(index);
                        }


                        createInfoInfo.Filename = prettyFilename;

                        CreateInfoInfos.Add(createInfoInfo.Name, createInfoInfo);
                        createInfoInfo = null;
                    }
                }
            }
        }
    }
}