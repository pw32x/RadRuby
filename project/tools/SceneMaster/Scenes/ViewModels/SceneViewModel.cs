﻿using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.CommandLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.Export;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Main;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Xml;

namespace SceneMaster.Scenes.ViewModels
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public class SceneViewModel : ObservableObject, IDisposable
    {
        // not the best place to put this, but it'll do for now.
        public static double ZoomFactor { get; set; } = 1;

        private bool m_ignoreChanges = false;
        private bool m_isModified = false;
        public bool IsModified
        {
            get => m_isModified;
            private set
            {
                if (!m_ignoreChanges)
                {
                    m_isModified = value; // always set it.
                    OnPropertyChanged(nameof(IsModified));
                }
            }
        }

        public ObservableCollection<EditorObjectViewModel> EditorObjectViewModels { get; set; } = new();

        private EditorObjectViewModel m_selectedEditorObjectViewModel;
        public EditorObjectViewModel SelectedEditorObjectViewModel
        {
            get => m_selectedEditorObjectViewModel;

            set
            {
                m_ignoreChanges = true;
                if (m_selectedEditorObjectViewModel != null)
                    m_selectedEditorObjectViewModel.IsSelected = false;

                SetProperty(ref m_selectedEditorObjectViewModel, value);

                if (m_selectedEditorObjectViewModel != null)
                    m_selectedEditorObjectViewModel.IsSelected = true;

                m_ignoreChanges = false;
            }
        }

        private Scene m_scene;
        public Scene Scene { get => m_scene; private set => SetProperty(ref m_scene, value); }

        private const uint EDITING_MODE_SCENE = 0;
        private const uint EDITING_MODE_OBJECTEDIT = 1;
        private const uint EDITING_MODE_OBJECTPLACE = 2;
        //private const uint EDITING_MODE_TERRAIN = 2;


        private uint m_currentEditingMode = 0;
        public uint CurrentEditingMode { get => m_currentEditingMode; set => SetProperty(ref m_currentEditingMode, value); }

        private int m_currentTileType = 0;
        public int CurrentTileType { get => m_currentTileType; set => SetProperty(ref m_currentTileType, value); }

        public TiledMapWrapper ForegroundTiledMap { get; }
        public TiledMapWrapper BackgroundTiledMap { get; }

        private Settings m_settings;

        EditorObjectLibraryViewModel EditorObjectInfoLibraryViewModel { get; set; }

        public SceneViewModel(Settings settings,
                              EditorObjectLibraryViewModel editorObjectInfoLibraryViewModel/*,
                              List<BitmapImage> tileTypeImages*/)
        {
            m_settings = settings;
            EditorObjectInfoLibraryViewModel = editorObjectInfoLibraryViewModel;
            Scene = new Scene(/*tileTypeImages*/);

            // attach
            Scene.PropertyChanged += Scene_PropertyChanged;
            Scene.EditorObjects.CollectionChanged += EditorObjects_CollectionChanged;

            foreach (var editorObject in Scene.EditorObjects)
            {
                var editorObjectViewModel = CreateEditorObjectViewModel(editorObject);
                EditorObjectViewModels.Add(editorObjectViewModel);
            }

            DeleteCommand = new RelayCommand(DeleteSelectedEditorObjectViewModel, 
                                             CanDeleteSelectedEditorObjectViewModel);

            
            ForegroundTiledMap = new(this, isForeground:true);
            BackgroundTiledMap = new(this, isForeground:false);

            ForegroundTiledMap.PropertyChanged += ForegroundTiledMap_PropertyChanged;
            BackgroundTiledMap.PropertyChanged += BackgroundTiledMap_PropertyChanged;
        }

        private void ForegroundTiledMap_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            OnPropertyChanged(nameof(ForegroundTiledMap));

            if (e.PropertyName == nameof(ForegroundTiledMap.TiledMapFilePath))
                Scene.ForegroundMapPath = ForegroundTiledMap.TiledMapFilePath;

            if (e.PropertyName == nameof(ForegroundTiledMap.Scroller) && ForegroundTiledMap.Scroller != null)
                Scene.ForegroundMapScrollerGuid = ForegroundTiledMap.Scroller.GameObject.Guid;
        }

        private void BackgroundTiledMap_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            OnPropertyChanged(nameof(BackgroundTiledMap));

            if (e.PropertyName == nameof(BackgroundTiledMap.TiledMapFilePath))
                Scene.BackgroundMapPath = BackgroundTiledMap.TiledMapFilePath;

            if (e.PropertyName == nameof(BackgroundTiledMap.Scroller) && BackgroundTiledMap.Scroller != null)
                Scene.BackgroundMapScrollerGuid = BackgroundTiledMap.Scroller.GameObject.Guid;
        }

        public void RunScene()
        {
            string tempLevelName = "sceneMasterTemp";

            // export to temporary file
            SceneExporter.ExportScene(Scene, 
                                      tempLevelName, 
                                      m_settings.SourceExportDirectory, 
                                      EditorObjectInfoLibraryViewModel.CommandLibrary);

            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            string buildMasterPath = Path.GetFullPath(baseDirectory + m_settings.BuildMasterPath);

            string workingDirectory = Path.GetFullPath(m_settings.GameBuildDirectory);
            string emulatorPath = Path.GetFullPath(m_settings.EmulatorPath);
            string pathToGameRom = Path.GetFullPath(m_settings.PathToGameRom);
            
            ProcessStartInfo buildMasterProcess = new ProcessStartInfo
            {
                FileName = buildMasterPath,
                Arguments = "config.bm build -DUSE_SCENEMASTER_LEVEL -SProjectName=" + Settings.GameRomName + " -SCopyToDailyFolder=false",
                WorkingDirectory = workingDirectory,
                UseShellExecute = false, // Set this to true if you want to use the system's default shell
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                //CreateNoWindow = true
            };

            StringBuilder sb = new StringBuilder();

            // Start the BuildMaster process
            try
            {
                using (Process process = Process.Start(buildMasterProcess))
                {
                    string output = process.StandardOutput.ReadToEnd();
                    StreamReader errorReader = process.StandardError;
                    var errorString = errorReader.ReadToEnd();

                    while (!process.StandardOutput.EndOfStream)
                    {
                        string outputLine = process.StandardOutput.ReadLine();
                        Console.WriteLine(outputLine);
                        sb.Append(outputLine);
                    }


                    // Wait for the process to exit
                    process.WaitForExit();
                    // Get the return code
                    int exitCode = process.ExitCode;

                    if (exitCode != 0) 
                    {
                        MessageBox.Show("BuildMaster build error. Error code: " + exitCode);
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error running BuildMaster process. Error: " + ex.Message);
                return;
            }

            /*
            // kill all the instances of the emulator
            var processes = Process.GetProcesses();
            var matchingProcesses = processes.Where(p => p.MainWindowTitle.Contains("Emulicious", StringComparison.OrdinalIgnoreCase));
            foreach (var process in processes)
            { 
                process.Kill(); 
            }
            */

            // start the game
            ProcessStartInfo emulatorProcess = new ProcessStartInfo
            {
                FileName = emulatorPath,
                Arguments = pathToGameRom,
                UseShellExecute = false, // Set this to true if you want to use the system's default shell
                RedirectStandardOutput = true
            };

            try
            {
                using (Process process = Process.Start(emulatorProcess))
                {
                    string output = process.StandardOutput.ReadToEnd();
                    // Wait for the process to exit
                    process.WaitForExit();
                    // Get the return code
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error running emulator process. Error: " + ex.Message);
                return;
            }
        }

        public ICommand DeleteCommand { get; }


        private void DeleteSelectedEditorObjectViewModel()
        {
            if (SelectedEditorObjectViewModel == null)
                return;

            Scene.EditorObjects.Remove(SelectedEditorObjectViewModel.EditorObject);
        }

        private bool CanDeleteSelectedEditorObjectViewModel()
        {
            return SelectedEditorObjectViewModel != null;
        }

        private void DeleteEditorObjectViewModel(EditorObject editorObjectToDelete)
        {
            var editorObjectViewModel = EditorObjectViewModels.FirstOrDefault(x => x.EditorObject == editorObjectToDelete);
            if (editorObjectViewModel == null)
                return;

            EditorObjectViewModels.Remove(editorObjectViewModel);
            editorObjectViewModel.PropertyChanged -= EditorObjectViewModel_PropertyChanged;

            Deselect(editorObjectViewModel);
        }

        public void Dispose()
        {
            // detach
            if (Scene != null)
            {
                foreach (var editorObjectViewModel in EditorObjectViewModels)
                {
                    editorObjectViewModel.PropertyChanged -= EditorObjectViewModel_PropertyChanged;
                }
                EditorObjectViewModels.Clear();

                Scene.PropertyChanged -= Scene_PropertyChanged;
                Scene.EditorObjects.CollectionChanged -= EditorObjects_CollectionChanged;

                Scene = null;
            }

            ForegroundTiledMap.Dispose();
            BackgroundTiledMap.Dispose();
        }

        private void EditorObjectViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
            if (e.PropertyName == nameof(EditorObject.Name))
            {
                EditorObjectViewModel editorObjectViewModel = sender as EditorObjectViewModel;
                int index = EditorObjectViewModels.IndexOf(editorObjectViewModel);
                EditorObjectViewModels.Remove(editorObjectViewModel);
                EditorObjectViewModels.Insert(index, editorObjectViewModel);
                Select(editorObjectViewModel);

                OnPropertyChanged(nameof(EditorObjectViewModels));
            }
        }

        private void Scene_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        private void EditorObjects_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            IsModified = true;

            Deselect(SelectedEditorObjectViewModel);

            if (e.NewItems != null)
            {
                foreach (var newEditorObject in e.NewItems.OfType<EditorObject>())
                {
                    var newEditorObjectViewModel = CreateEditorObjectViewModel(newEditorObject);
                    EditorObjectViewModels.Add(newEditorObjectViewModel);
                }
            }

            if (e.OldItems != null)
            {
                foreach (var editorObjectToDelete in e.OldItems.OfType<EditorObject>())
                {
                    DeleteEditorObjectViewModel(editorObjectToDelete);
                }
            }
        }

        private EditorObjectViewModel CreateEditorObjectViewModel(EditorObject newEditorObject)
        {
            EditorObjectViewModel newEditorObjectViewModel = null;

            if (newEditorObject is CommandObject commandObject)
            {
                newEditorObjectViewModel = new CommandObjectViewModel(commandObject, this);
            }
            else if (newEditorObject is GameObject gameObject)
            {
                newEditorObjectViewModel = new GameObjectViewModel(gameObject, this);
            }

            newEditorObjectViewModel.PropertyChanged += EditorObjectViewModel_PropertyChanged;
            return newEditorObjectViewModel;
        }

        internal void Load(string filePath)
        {
            m_ignoreChanges = true;

            var root = XmlUtils.OpenXmlDocument(filePath, nameof(Scene));

            Scene.LoadFromXml(root, filePath, EditorObjectInfoLibraryViewModel);

            if (!string.IsNullOrEmpty(Scene.ForegroundMapPath))
                ForegroundTiledMap.LoadTiledMap(Scene.ForegroundMapPath, Scene.ForegroundMapScrollerGuid);

            if (!string.IsNullOrEmpty(Scene.BackgroundMapPath))
                BackgroundTiledMap.LoadTiledMap(Scene.BackgroundMapPath, Scene.BackgroundMapScrollerGuid);

            m_ignoreChanges = false;

            IsModified = false;
            OnPropertyChanged(nameof(Scene));
        }

        internal void Save(string filePath)
        {
            var doc = new XmlDocument();

            var root = doc.CreateElement(nameof(Scene));
            doc.AppendChild(root);

            Scene.SaveToXmlElement(doc, root, filePath);

            doc.Save(filePath);
            IsModified = false;
        }

        internal void Select(EditorObjectViewModel editorObjectViewModel)
        {
            if (SelectedEditorObjectViewModel == editorObjectViewModel)
                return;

            SelectedEditorObjectViewModel = editorObjectViewModel;
        }

        internal void Deselect(EditorObjectViewModel editorObjectViewModel)
        {
            if (SelectedEditorObjectViewModel == editorObjectViewModel)
            {
                SelectedEditorObjectViewModel = null;
            }
        }

        internal void CreateEditorObject(int mapX, int mapY)
        {
            if (EditorObjectInfoLibraryViewModel.SelectedEditorObjectInfo == null)
                return;

            Scene.CreateEditorObject(mapX, mapY, EditorObjectInfoLibraryViewModel.SelectedEditorObjectInfo);
        }

        internal void MouseLeftButtonDown(int mapX, int mapY)
        {
            switch (CurrentEditingMode) 
            {
            case EDITING_MODE_OBJECTPLACE:
            case EDITING_MODE_OBJECTEDIT:
            {
                CreateEditorObject(mapX, mapY);
            }
            break;
            /*
            case EDITING_MODE_TERRAIN:

                int tileX = mapX / Scene.TiledMap.TileWidth;
                int tileY = mapY / Scene.TiledMap.TileHeight;

                SetTerrainTileType(tileX, tileY);

            break;
            */
            }
        }

        /*
        public void SetTerrainTileType(int tileX, int tileY)
        {
            m_scene.SetTerrainTileType(tileX, tileY, m_currentTileType);
        }
        */

    }
}
