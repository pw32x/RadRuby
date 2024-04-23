using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace BuildMaster
{
    class Config
    {
        public CompilationSettings CompilationSettings { get; private set; }

        public DateTime LastConfigFileWriteTime { get; private set; }
        public DateTime LastApplicationWriteTime { get; private set; }

        public void Load(string path)
        {
            if (!File.Exists(path))
                throw new Exception("Path for config file not found");

            XmlDocument xmlDocument = new XmlDocument();

            xmlDocument.Load(path);

            LoadSettings(xmlDocument);
            LoadTools(xmlDocument);
            LoadToolJobs(xmlDocument);

            LoadIncludes(xmlDocument);

            BuildToolDestinationFoldersList();


            CompilationSettings = new CompilationSettings(GetSetting("outFolder"));

            LastConfigFileWriteTime = File.GetLastWriteTime(path);

            string appPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            LastApplicationWriteTime = System.IO.File.GetLastWriteTime(appPath);
        }

        public IEnumerable<string> BuildSourceDestinationFolders()
        {
            var sourceDestinationFolders = new HashSet<string>();

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                sourceDestinationFolders.Add(CompilationSettings.OutFolder + toolDestinationFolder);
            }

            return sourceDestinationFolders;
        }

        public IEnumerable<string> GetToolExportFolders()
        {
            var toolExportFolders = new HashSet<string>();

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                toolExportFolders.Add(toolDestinationFolder);
            }

            return toolExportFolders;
        }


        public IEnumerable<string> BuildListOfHeaderFiles()
        {
            var headerFiles = new HashSet<string>();

            string[] headerFileExtensions = { ".h" };

            var currentDirectory = Directory.GetCurrentDirectory();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourceFolder in sourceSet.SourceFolders)
                {
                    if (Directory.Exists(sourceFolder))
                    {
                        DirectoryInfo directoryInfo = new DirectoryInfo(sourceFolder);
                        FileInfo[] files = directoryInfo.GetFiles();

                        var filteredFiles = files.Where(file => headerFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                        foreach (var filteredFile in filteredFiles)
                        {
                            string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                            headerFiles.Add(relativePath);
                        }
                    }
                }
            }

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                if (Directory.Exists(toolDestinationFolder))
                {
                    DirectoryInfo directoryInfo = new DirectoryInfo(toolDestinationFolder);
                    FileInfo[] files = directoryInfo.GetFiles();

                    var filteredFiles = files.Where(file => headerFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                    foreach (var filteredFile in filteredFiles)
                    {
                        string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                        headerFiles.Add(relativePath);
                    }
                }
            }

            return headerFiles;
        }

        private void LoadSettings(XmlDocument xmlDocument)
        {
            XmlNodeList settingsNodes = xmlDocument.SelectNodes("/BuildMaster/Settings/Setting");

            if (settingsNodes != null)
            {
                foreach (XmlNode settingNode in settingsNodes)
                {
                    string name = settingNode.Attributes["name"].Value;
                    string value = settingNode.Attributes["value"].Value;

                    m_settings[name.ToLower()] = value;
                }
            }
        }

        // Tools
        private void LoadTools(XmlDocument xmlDocument)
        {
            XmlNodeList toolsNodes = xmlDocument.SelectNodes("/BuildMaster/Tools/Tool");

            if (toolsNodes != null)
            {
                foreach (XmlNode toolNode in toolsNodes)
                {
                    string name = toolNode.Attributes["name"].Value;
                    string path = toolNode.Attributes["path"].Value;
                    string flags = toolNode.Attributes["flags"]?.Value ?? "";
                    string info = toolNode.Attributes["info"]?.Value ?? "";

                    var newToolInfo = new ToolInfo(name,
                                                   path,
                                                   flags,
                                                   info);

                    var additionalExportFolderFlagNodes = toolNode.SelectNodes("AdditionalExportFolderFlag");

                    foreach (XmlNode additionalExportFolderFlagNode in additionalExportFolderFlagNodes)
                    {
                        string flag = additionalExportFolderFlagNode.Attributes["flag"]?.Value ?? "";

                        if (string.IsNullOrEmpty(flag))
                            continue;

                        string useAsIncludeFolder = additionalExportFolderFlagNode.Attributes["useasincludefolder"]?.Value ?? "";

                        var additionalExportFolder = new AdditionalExportFolder() { FlagName = flag, 
                                                                                    UseAsIncludeFolder = useAsIncludeFolder.ToLower() == "true" };

                        newToolInfo.AdditionalExportFolders.Add(additionalExportFolder);
                    }

                    m_toolInfos[name.ToLower()] = newToolInfo;
                }
            }
        }

        private void LoadToolJobs(XmlDocument xmlDocument)
        {
            XmlNodeList toolJobNodes = xmlDocument.SelectNodes("/BuildMaster/ToolJobs/ToolJob");

            if (toolJobNodes != null)
            {
                foreach (XmlNode toolJob in toolJobNodes)
                {
                    string toolName = toolJob.Attributes["tool"].Value;
                    string source = toolJob.Attributes["source"].Value;
                    string destination = toolJob.Attributes["destination"].Value;
                    string bank = toolJob.Attributes["bank"]?.Value;
                    string extraFlags = toolJob.Attributes["extraflags"]?.Value;
                    uint.TryParse(bank, out uint bankNumber);

                    var toolInfo = GetTool(toolName);

                    var additionalDestinations = new List<string>();

                    foreach (var additionalExportFolder in toolInfo.AdditionalExportFolders)
                    {
                        string value = toolJob.Attributes[additionalExportFolder.FlagName]?.Value;

                        if (string.IsNullOrEmpty(value))
                            continue;

                        extraFlags += " -" + additionalExportFolder.FlagName + " " + value;

                        additionalDestinations.Add(value);

                        if (additionalExportFolder.UseAsIncludeFolder)
                            IncludePaths.Add(Utils.NormalizePath(value));
                    }

                    //var destinationFolders = toolJob.Attributes.

                    var newToolJob = new ToolJobInfo(toolName,
                                                     Utils.NormalizePath(source),
                                                     Utils.NormalizePath(destination),
                                                     extraFlags,
                                                     bankNumber,
                                                     additionalDestinations);


                    m_toolJobs.Add(newToolJob);

                    // create a source set for the tool job.
                    // the source set's source is the destination of the tool job.

                    var sourceSet = new SourceSet(bank);

                    if (Utils.IsFileOrFileSpec(destination))
                    {
                        sourceSet.SourceFolders.Add(Utils.GetPathFromFileOrFileSpec(destination));
                    }
                    else
                    {
                        source = Utils.NormalizePath(destination);
                        sourceSet.SourceFolders.Add(destination);
                    }

                    sourceSet.SourcePaths.Add(destination);

                    foreach (var additionalDestination in additionalDestinations)
                    {
                        sourceSet.SourceFolders.Add(additionalDestination);
                        sourceSet.SourcePaths.Add(additionalDestination);
                    }

                    m_sourceSets.Add(sourceSet);
                }
            }
        }

        // Include paths
        public HashSet<string> IncludePaths { get; } = new HashSet<string>();
        private void LoadIncludes(XmlDocument xmlDocument)
        {
            XmlNodeList includeNodes = xmlDocument.SelectNodes("/BuildMaster/Include");

            if (includeNodes != null)
            {
                foreach (XmlNode includeNode in includeNodes)
                {
                    string includePath = includeNode.Attributes["path"].Value;

                    IncludePaths.Add(Utils.NormalizePath(includePath));
                }
            }
        }

        // Source Sets

        class SourceSet
        {
            public SourceSet(string bank = "")
            {
                Bank = bank;
            }

            public HashSet<string> SourcePaths { get; } = new HashSet<string>();
            public HashSet<string> SourceFolders { get; } = new HashSet<string>();
            public string Bank { get; }
        }

        HashSet<SourceSet> m_sourceSets = new HashSet<SourceSet>();

        // Settings
        Dictionary<string, string> m_settings = new Dictionary<string, string>();

        public string GetSetting(string name)
        {
            if (!m_settings.ContainsKey(name.ToLower()))
                return "Not found";

            return m_settings[name.ToLower()];
        }

        public string ProjectName { get { return GetSetting("ProjectName"); } }
        public string WorkingDirectory { get { return GetSetting("WorkingDirectory"); } }
        public string ResourceIncludeExportFolder { get { return GetSetting("resourceIncludeExportFolder"); } }

        // Tools

        public class AdditionalExportFolder
        {
            public string FlagName { get; set; }
            public bool UseAsIncludeFolder { get; set; }
        }

        public class ToolInfo
        {
            public ToolInfo(string name,
                            string path,
                            string flags,
                            string info)
            {
                Name = name.ToLower();
                Path = path.ToLower();
                Flags = flags;
                Info = info;
            }

            public string Name { get; }
            public string Path { get; }
            public string Flags { get; }
            public string Info { get; }
            public List<AdditionalExportFolder> AdditionalExportFolders { get; } = new List<AdditionalExportFolder>();
        }

        private Dictionary<string, ToolInfo> m_toolInfos = new Dictionary<string, ToolInfo>();
        public IEnumerable<ToolInfo> ToolInfos => m_toolInfos.Values;

        public ToolInfo GetTool(string toolName) => m_toolInfos[toolName.ToLower()];


        // Tool Jobs 
        public class ToolJobInfo
        {
            public ToolJobInfo(string toolName,
                               string source,
                               string destination,
                               string extraFlags,
                               uint bankNumber,
                               List<string> additionalDestinations)
            {
                ToolName = toolName.ToLower();
                SourcePath = source.ToLower();
                DestinationPath = destination.ToLower();
                ExtraFlags = extraFlags;
                BankNumber = bankNumber;
                AdditionalDestinations = additionalDestinations;
            }

            public string ToolName { get; }
            public string SourcePath { get; }
            public string DestinationPath { get; }
            public string ExtraFlags { get; }
            public uint BankNumber { get; }
            public List<string> AdditionalDestinations;
        }

        private List<ToolJobInfo> m_toolJobs = new List<ToolJobInfo>();
        public IEnumerable<ToolJobInfo> ToolJobs => m_toolJobs;

        // Destinations List

        private List<string> m_toolDestinationFolders;
        public IEnumerable<string> ToolDestinationFolders => m_toolDestinationFolders;

        private void BuildToolDestinationFoldersList()
        {
            var uniqueDirectories = new HashSet<string>();

            foreach (var toolJob in m_toolJobs)
            {
                string directory = toolJob.DestinationPath;

                if (Path.HasExtension(directory))
                    directory = Path.GetDirectoryName(directory);

                uniqueDirectories.Add(directory);

                foreach (var additionalDestination in toolJob.AdditionalDestinations)
                {
                    uniqueDirectories.Add(additionalDestination);
                }
            }

            m_toolDestinationFolders = uniqueDirectories.ToList();
        }

        internal void AddOrOverrideSetting(string settingName, string value)
        {
            m_settings[settingName.ToLower()] = value;
        }
    }

}
