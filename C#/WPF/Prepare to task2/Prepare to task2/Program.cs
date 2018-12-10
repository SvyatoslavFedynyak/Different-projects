using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Prepare_to_task2
{
    #region MVVM
    delegate void OnPropertyChangedDelegate(object sender, EventArgs e);
    interface INotifyPropertyChanged
    {
        event OnPropertyChangedDelegate OnPropertyChanged;
    }
    enum CatColor
    {
        Grey, Black, White, Brown
    }
    class Cat : INotifyPropertyChanged
    {
        string name;
        int age;
        CatColor color;
        public event OnPropertyChangedDelegate OnPropertyChanged;
        public Cat() { }
        string Name
        {
            get { return name; }
            set { name = value; }
        }
        int Age
        {
            get { return age; }
            set { age = value; }
        }
        CatColor Color
        {
            get { return color; }
            set { color = value; }
        }
    }
    class VievModel
    {
        Cat model;


    }
    #endregion
    #region Command
    interface ICommand
    {
        void Execute();
    }
    class PrintHeart : ICommand
    {
        public void Execute()
        {
            Console.WriteLine("");
        }
    } 
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
