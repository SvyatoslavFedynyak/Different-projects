using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using My_Own_Game;
namespace SimpleSCharpApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.SetWindowSize(100, 50);
            Console.SetBufferSize(100, 50);
            int num;
            Console.WriteLine("Enter number:");
            num = Convert.ToInt32(Console.ReadLine());
            Console.Clear();
            Settings sett = new Settings();
            sett.console_high_size = Console.BufferHeight;
            sett.console_wigth_size = Console.BufferWidth;
            sett.count_of_enemy = num;
            sett.difficult = 0;
            sett.start_hp = 10;
            sett.SetHitBox(2, 2, 2, 2);
            List<Enemy> enemy_list = new List<Enemy>();
            Game.SetEnemys(enemy_list);
            Game.SetSettings(sett);
            for (int i = 0; i < num; i++)
            {
                Game.SpawnEnemy();
            }
            Protagonist MH = new Protagonist(sett.console_wigth_size / 2, sett.console_high_size / 2, sett.start_hp);
            Game.SetMainHero(MH);
            Game.StartGame();
        }
    }
}
