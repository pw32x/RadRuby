using SceneMaster.Scenes.ViewModels;
using SceneMaster.Scenes.Models;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace SceneMaster.Scenes.Views
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public partial class SceneView : UserControl
    {
        private SceneViewModel m_sceneViewModel;
        private Scene m_scene;

        public SceneView()
        {
            InitializeComponent();
        }

        private void Button_ClickReset(object sender, System.Windows.RoutedEventArgs e)
        {
            ZoomBorder?.Reset();
        }

        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (m_sceneViewModel != null) 
            { 
                // convert the position clicked on the ForegroundTileMapBitmapImage 
                // to a position on the tilemap.
                var mapPos = e.GetPosition(ForegroundTileMapBitmapImage);

                int mapX = (int)((mapPos.X / ForegroundTileMapBitmapImage.ActualWidth) * ForegroundTileMapBitmapImage.Source.Width);
                int mapY = (int)((mapPos.Y / ForegroundTileMapBitmapImage.ActualHeight) * ForegroundTileMapBitmapImage.Source.Height);


                m_sceneViewModel.MouseLeftButtonDown(mapX, mapY);
            }
        }

        private void ForegroundTileMapBitmapImage_LayoutUpdated(object sender, EventArgs e)
        {
            SceneViewModel.ZoomFactor = ZoomBorder.ZoomX;
        }

        private void DrawGridLines()
        {
            if (m_sceneViewModel == null ||
                m_sceneViewModel.Scene == null ||
                m_sceneViewModel.ForegroundTiledMap.TiledMap == null)
                return;


            int tileWidth = m_sceneViewModel.ForegroundTiledMap.TiledMap.TileWidth;
            int tileHeight = m_sceneViewModel.ForegroundTiledMap.TiledMap.TileHeight;

            int mapWidth = m_sceneViewModel.ForegroundTiledMap.TiledMap.Width * tileWidth;
            int mapHeight = m_sceneViewModel.ForegroundTiledMap.TiledMap.Height * tileHeight;

            GridCanvas.Children.Clear();


            DrawingVisual drawingVisual = new DrawingVisual();
            using (DrawingContext drawingContext = drawingVisual.RenderOpen())
            {
                Color lineColor = Colors.Black;
                byte alphaValue = 255; // Adjust the alpha value as needed (0 to 255 for transparency)

                Pen pen = new Pen(new SolidColorBrush(Color.FromArgb(alphaValue, lineColor.R, lineColor.G, lineColor.B)), .25);
                pen.DashStyle = new DashStyle(new double[] { 0, 2 }, 0); // Adjust the dash and gap lengths as needed

                // Draw vertical grid lines
                for (double x = 0; x <= mapWidth; x += tileWidth) // Adjust the interval as needed
                {
                    drawingContext.DrawLine(pen, new Point(x, 0), new Point(x, mapHeight));
                }

                // Draw horizontal grid lines
                for (double y = 0; y <= mapHeight; y += tileHeight) // Adjust the interval as needed
                {
                    drawingContext.DrawLine(pen, new Point(0, y), new Point(mapWidth, y));
                }
            }

            // Create a DrawingImage from the DrawingVisual
            DrawingImage drawingImage = new DrawingImage(drawingVisual.Drawing);

            // Create an Image control and set its Source to the DrawingImage
            Image image = new Image { Source = drawingImage };

            // Add the Image control to the Canvas
            GridCanvas.Children.Add(image);
        }

        private void SceneMasterSceneView_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            //DrawGridLines();
        }

        private void SceneMasterSceneView_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            m_scene = null;

            if (m_sceneViewModel != null)
            {
                m_sceneViewModel.PropertyChanged -= SceneViewModel_PropertyChanged;
                m_sceneViewModel = null;
            }

            if (DataContext is SceneViewModel sceneViewModel)
            {
                m_sceneViewModel = sceneViewModel;
                m_scene = sceneViewModel.Scene;

                if (m_sceneViewModel != null) 
                {
                    m_sceneViewModel.PropertyChanged += SceneViewModel_PropertyChanged;
                }
            }

            DrawGridLines();
        }

        private void SceneViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(TiledMapWrapper.TiledMapBitmapSource))
                DrawGridLines();
        }
    }
}
