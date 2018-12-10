using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace WPFWithoutXAML
{
    class MainWindow : Window
    {
        private Button exitButton;

        public MainWindow(string windowTitle, int heigh, int width)
        {
            #region Button add
            exitButton = new Button();
            exitButton.Click += ExitButton_Click;
            exitButton.Content = "Exit";
            exitButton.Height = 300;
            exitButton.Width = 400;
            this.AddChild(exitButton); 
            #endregion
            Title = windowTitle;
            WindowStartupLocation = WindowStartupLocation.CenterScreen;
            Height = heigh;
            Width = width;
            #region Events
            Closing += MainWindow_Closing;
            Closed += MainWindow_Closed;
            MouseMove += MainWindow_MouseMove;
            KeyDown += MainWindow_KeyDown;
            #endregion
        }

        private void MainWindow_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            exitButton.Content = e.Key.ToString();
        }

        private void MainWindow_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
        {
            Title = e.GetPosition(this).ToString();
        }

        private void MainWindow_Closed(object sender, EventArgs e)
        {
            MessageBox.Show("Pedor!");
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            string msg = "Do you want to close without saving?";
            MessageBoxResult result = MessageBox.Show(msg, "My app", MessageBoxButton.YesNo, MessageBoxImage.Warning);
            if (result == MessageBoxResult.No)
            {
                e.Cancel = true;
            }
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            if ((bool)Application.Current.Properties["/GodMode"])
            {
                MessageBox.Show("Cheater!");
            }
            Close();
        }
    }
    class Program : Application
    {
        static void AppStartUp(object sender, StartupEventArgs e)
        {
            Current.Properties["GodMode"] = false;
            foreach (string arg in e.Args)
            {
                if (arg.ToLower() == "/godmode") 
                {
                    Current.Properties["/GodMode"] = true;
                    break;
                }
            }
            MainWindow mainwWindow = new MainWindow("Hello fucking world!", 600, 800);
            mainwWindow.Show();
        }
        static void AppExit(object sender, ExitEventArgs e)
        {
            MessageBox.Show("Bye fucking world!");
        }
        [STAThread]
        static void Main(string[] args)
        {
            Program app = new Program();
            app.Startup += AppStartUp;
            app.Exit += AppExit;
            app.Run();
        }
    }
}
