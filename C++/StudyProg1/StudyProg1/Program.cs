using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudyProg1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.ReadLine();
            FirstMethod();
            Console.ReadLine();
        }

        private static void FirstMethod()
        {
            Console.Title = "My first C# prog";
            Console.ForegroundColor = ConsoleColor.Green;
            Console.BackgroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("Hello bitches)");
        }
    }
}
