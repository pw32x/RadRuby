using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Scenes.ViewModels;
using System.Collections.Generic;

namespace SceneMaster.GameObjectTemplates.ViewModels
{
    public class GameObjectViewModel : EditorObjectViewModel
    {
        public GameObjectViewModel(GameObject gameObject, SceneViewModel sceneViewModel) : base(gameObject, sceneViewModel)
        {

        }

        public GameObject GameObject => EditorObject as GameObject;
    }
}
