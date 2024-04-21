using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace tmx2c
{

    class Tmx2CRunner
    {
        string [] mArgs;

        private string SourceFolder;
        private string TmxExtension = "tmx";

        private string DestinationFolder;

        public Tmx2CRunner(string [] args)
        {
            mArgs = args;
        }

        private void ParseArguments(string[] args)
        {
            if (args.Length == 0)
                throw new Exception("No arguments passed");

            SourceFolder = args[0];

            if (!String.IsNullOrEmpty(SourceFolder) && !SourceFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                SourceFolder += Path.DirectorySeparatorChar;

            if (args.Length > 1)
                DestinationFolder = args[1];

            if (!String.IsNullOrEmpty(DestinationFolder) && !DestinationFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                DestinationFolder += Path.DirectorySeparatorChar;
        }

        public int Run()
        {
            // Get application stuff
            string applicationLocation = System.Reflection.Assembly.GetEntryAssembly().Location;
            DateTime applicationTime = File.GetLastWriteTime(applicationLocation);

            ParseArguments(mArgs);

            // Get all the maps files in the maps folder.
            var mapFilenames = Directory.GetFiles(SourceFolder, "*." + TmxExtension);

            // Load maps
            // 
            List<Map> maps = LoadMaps(mapFilenames);

            // Check for any maps that need to be updated
            // 
            List<Map> mapsThatNeedUpdating = GetMapsThatNeedUpdating(maps, 
                                                                     applicationTime, 
                                                                     new DateTime() /*gameObjectsFileTime*/);

            if (mapsThatNeedUpdating.Count() > 0 && !Directory.Exists(DestinationFolder))
                Directory.CreateDirectory(DestinationFolder);

            if (mapsThatNeedUpdating.Count > 0)
            {
                ExportMaps(mapsThatNeedUpdating, DestinationFolder, Map.ExportMode.StripMap);
            }
            else
            {
                Console.WriteLine("No maps need updating.");
            }

            return 0;
        }

        private void ExportMaps(List<Map> mapsToExport, 
                                string mapsExportLocation, 
                                Map.ExportMode exportMode)
        {
            foreach (var mapToExport in mapsToExport)
            {
                Console.WriteLine("Exporting Map: \"" + mapToExport.MapName + "\"");
                mapToExport.Export(exportMode);
            }
        }

        private List<Map> LoadMaps(IEnumerable<string> mapFilenames)
        {
            var maps = new List<Map>();

            foreach (var mapFilename in mapFilenames)
            {
                maps.Add(new Map(mapFilename));
            }

            return maps;
        }

        private List<Map> GetMapsThatNeedUpdating(List<Map> maps, 
                                                  DateTime applicationTime, 
                                                  DateTime gameObjectsFileTime)
        {
            var mapsThatNeedUpdating = new List<Map>();

            foreach (var map in maps)
            {
                if (map.NeedsUpdate(applicationTime, gameObjectsFileTime, SourceFolder, DestinationFolder) ||
                    Debugger.IsAttached)
                {
                    mapsThatNeedUpdating.Add(map);
                }
            }

            return mapsThatNeedUpdating;
        }
    }
}
