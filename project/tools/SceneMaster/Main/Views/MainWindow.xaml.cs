using System.Windows;
using SceneMaster.Main.ViewModels;

namespace SceneMaster
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = MainViewModel;

            Width = MainViewModel.Settings.MainWindowSize.Width;
            Height = MainViewModel.Settings.MainWindowSize.Height;
            Left = MainViewModel.Settings.MainWindowLeft;
            Top = MainViewModel.Settings.MainWindowTop;
            WindowState = MainViewModel.Settings.MainWindowState;
        }

        public MainViewModel MainViewModel { get; } = new MainViewModel();

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (!MainViewModel.CheckForSave())
                e.Cancel = true;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            MainViewModel.Settings.MainWindowSize = e.NewSize;
        }

        private void Window_LocationChanged(object sender, System.EventArgs e)
        {
            MainViewModel.Settings.MainWindowLeft = Left;
            MainViewModel.Settings.MainWindowTop = Top;
        }

        private void Window_StateChanged(object sender, System.EventArgs e)
        {
            MainViewModel.Settings.MainWindowState = WindowState;
        }
    }
}
