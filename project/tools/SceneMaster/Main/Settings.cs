﻿using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Utils;
using System;
using System.IO;
using System.Windows;
using System.Xml.Serialization;

namespace SceneMaster.Main
{
    public class Settings : ObservableObject
    {
        private string m_settingsFilename = "settings.xml";

        private bool m_reloadLastScene = false;
        public bool ReloadLastScene { get => m_reloadLastScene; set => SetProperty(ref m_reloadLastScene, value); }

        private string m_lastLoadedSceneFilename = "";
        public string LastLoadedSceneFilename { get => m_lastLoadedSceneFilename; set => SetProperty(ref m_lastLoadedSceneFilename, value); }

        private string m_gameObjectTemplatesDirectory = "gamedata\\gameobjecttemplates";
        public string GameObjectTemplatesDirectory { get => m_gameObjectTemplatesDirectory; set => SetProperty(ref m_gameObjectTemplatesDirectory, value); }

        private string m_sourceDirectory = "source";
        public string SourceDirectory { get => m_sourceDirectory; set => SetProperty(ref m_sourceDirectory, value); }

        private string m_sourceExportDirectory = "source\\client\\exported";
        public string SourceExportDirectory { get => m_sourceExportDirectory; set => SetProperty(ref m_sourceExportDirectory, value); }

        private string m_gameBuildDirectory = "build";
        public string GameBuildDirectory { get => m_gameBuildDirectory; set => SetProperty(ref m_gameBuildDirectory, value); }

        private string m_buildMasterPath = "..\\..\\..\\tools\\BuildMaster\\bin\\Release\\net8.0\\BuildMaster.exe";
        public string BuildMasterPath { get => m_buildMasterPath; set => SetProperty(ref m_buildMasterPath, value); }

        private string m_emulatorPath = "..\\..\\..\\Emulicious-with-Java64\\Emulicious.exe";
        public string EmulatorPath { get => m_emulatorPath; set => SetProperty(ref m_emulatorPath, value); }

        public const string GameRomName = "SceneMasterTemp";

        private string m_lastSceneSaveLocation = "";
        public string LastSceneLocation { get => m_lastSceneSaveLocation; set => SetProperty(ref m_lastSceneSaveLocation, value); }

/*
        // how to use this for when the user chooses a new map?
        private string m_lastImportLocation = "";
        public string LastImportLocation { get => m_lastImportLocation; set => SetProperty(ref m_lastImportLocation, value); }
*/
        private string m_lastExportLocation = "";
        public string LastExportLocation { get => m_lastExportLocation; set => SetProperty(ref m_lastExportLocation, value); }


        private string m_pathToGameRom = "out\\" + GameRomName + ".sms";
        public string PathToGameRom { get => m_pathToGameRom; set => SetProperty(ref m_pathToGameRom, value); }

        private Size m_mainWindowSize;
        public Size MainWindowSize { get => m_mainWindowSize; set => SetProperty(ref m_mainWindowSize, value); }
        public double MainWindowTop { get; set; }
        public double MainWindowLeft { get; set; }
        public WindowState MainWindowState { get; set; }

        public void Load()
        {
            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);
            string fullPath = appFolder + m_settingsFilename;

            if (!File.Exists(fullPath))
                return;

            XmlSerializer serializer = new XmlSerializer(typeof(Settings));

            // Deserialize the object from XML
            using (TextReader reader = new StreamReader(fullPath))
            {
                var temp = serializer.Deserialize(reader);

                // Update the properties of the existing object with the deserialized data
                // This assumes that the properties have public setters
                foreach (var property in typeof(Settings).GetProperties())
                {
                    var deserializedValue = property.GetValue(temp);
                    property.SetValue(this, deserializedValue);
                }
            }
        }

        public void Save()
        {
            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);

            // Create an XmlSerializer for the type of the object
            XmlSerializer serializer = new XmlSerializer(typeof(Settings));

            // Serialize the object to XML
            using (TextWriter writer = new StreamWriter(appFolder + m_settingsFilename))
            {
                serializer.Serialize(writer, this);
            }
        }
    }
}
