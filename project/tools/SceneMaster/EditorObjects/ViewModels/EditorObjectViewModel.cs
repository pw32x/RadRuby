﻿using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.ViewModels;
using System;
using System.ComponentModel;
using System.Windows.Input;

namespace SceneMaster.EditorObjects.ViewModels
{
    public class EditorObjectViewModel : ObservableObject
    {
        [Browsable(false)]
        public ICommand ResetSpawnPointPositionCommand { get; }

        [Browsable(false)]
        public bool HasNoObjectData => EditorObject.ObjectData == null;

        public EditorObjectViewModel(EditorObject editorObject,
                                     SceneViewModel sceneViewModel)
        {
            EditorObject = editorObject;
            SceneViewModel = sceneViewModel;

            ResetSpawnPointPositionCommand = new RelayCommand(ResetSpawnPointPosition);
        }

        private void ResetSpawnPointPosition()
        {
            SpawnX = X;
            SpawnY = Y;
        }

        internal void Select()
        {
            SceneViewModel.Select(this);
        }

        internal void Deselect()
        {
            SceneViewModel.Deselect(this);
        }

        public string Name
        {
            get => EditorObject.Name;
            set
            {
                EditorObject.Name = value;
                OnPropertyChanged();
            }
        }

        public int X
        {
            get => EditorObject.X;
            set
            {
                EditorObject.X = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SpawnAreaX));
            }
        }

        public int SpawnAreaX => X - 256;


        public int Y
        {
            get => EditorObject.Y;
            set
            {
                EditorObject.Y = value;
                OnPropertyChanged();
            }
        }

        public int SpawnX
        {
            get => EditorObject.SpawnX;
            set
            {
                EditorObject.SpawnX = value;
                OnPropertyChanged();
            }
        }

        public int SpawnY
        {
            get => EditorObject.SpawnY;
            set
            {
                EditorObject.SpawnY = value;
                OnPropertyChanged();
            }
        }

        public bool SpawnPointIsIndependant
        {
            get => EditorObject.SpawnPointIsIndependant;
            set
            {
                EditorObject.SpawnPointIsIndependant = value;
                OnPropertyChanged();
            }
        }

        public double Width { get => EditorObject.EditorObjectInfo.Visual.Width; }
        public double Height { get => EditorObject.EditorObjectInfo.Visual.Height; }

        [DisplayName("Editor Object Type")]
        public string EditorObjectTypeName => EditorObject.EditorObjectType.ToString();

        [System.ComponentModel.Browsable(false)]
        public EditorObject EditorObject { get; set; }

        [System.ComponentModel.Browsable(false)]
        public SceneViewModel SceneViewModel { get; internal set; }

        private bool m_isSelected = false;

        [System.ComponentModel.Browsable(false)]
        public bool IsSelected
        {
            get => m_isSelected;
            set
            {
                SetProperty(ref m_isSelected, value);
            }
        }
    }
}
