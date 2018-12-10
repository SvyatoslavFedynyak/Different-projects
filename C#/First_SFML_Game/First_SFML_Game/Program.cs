using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace First_SFML_Game
{
    class Program
    {
        static void Main(string[] args)
        {
            Game.Game_Settings.Game_Resolution = new Resolution(1440, 900);
            Game.Name = "My Game";

            Game.Start_Game();
        }
    }
}
