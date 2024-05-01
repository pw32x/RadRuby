using SceneMaster.CreateInfo.Models;
using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Scenes.ViewModels;
using System.Collections.Generic;

namespace SceneMaster.GameObjectTemplates.ViewModels
{
    internal class GameObjectViewModel : EditorObjectViewModel
    {
        public GameObjectViewModel(GameObject gameObject, SceneViewModel sceneViewModel) : base(gameObject, sceneViewModel)
        {

        }

        public GameObject GameObject => EditorObject as GameObject;

        public List<CreateInfoField> CreateInfoFields => GameObject.CreateInfoFields;
    }
}
