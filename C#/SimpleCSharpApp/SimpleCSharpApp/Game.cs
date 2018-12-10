using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace My_Own_Game
{
    class SurfacePoint
    {
        internal char Texture;
        internal bool occupied;
        internal GameObject Occupier;
        public SurfacePoint() { }
    }
    class Surface
    {
        internal SurfacePoint[,] Field;
        public Surface() { }
        public Surface(int x_size, int y_size)
        {
            Field = new SurfacePoint[x_size, y_size];
        }
    }
    struct Coordinates
    {
        public int XPos;
        public int YPos;
        Coordinates(int xpos = 0, int ypos = 0)
        {
            XPos = xpos;
            YPos = ypos;
        }
    }
    struct HitBox
    {
        public int Up, Down, Left, Right;
        HitBox(int u = 0, int d = 0, int l = 0, int r = 0)
        {
            Up = u;
            Down = d;
            Left = l;
            Right = r;
        }
    }
    class GameObject
    {
        protected Coordinates ObjectCoordinat;
        internal HitBox ObjectHitBox;
        protected void Set_HitBox(int Up, int Down, int Left, int Right)
        {
            ObjectHitBox.Up = Up;
            ObjectHitBox.Right = Right;
            ObjectHitBox.Left = Left;
            ObjectHitBox.Down = Down;
        }
        public GameObject() { }
        public GameObject(int x, int y)
        {
            ObjectCoordinat.XPos = x;
            ObjectCoordinat.YPos = y;
        }
        public int ReturnXPos() { return ObjectCoordinat.XPos; }
        public int ReturnYPos() { return ObjectCoordinat.YPos; }
        public void Move(string Way)
        {
            if (Way == "Up")
            {
                ObjectCoordinat.YPos--;
            }
            else if (Way == "Down")
            {
                ObjectCoordinat.YPos++;
            }
            else if (Way == "Left")
            {
                ObjectCoordinat.XPos--;
            }
            else if (Way == "Right")
            {
                ObjectCoordinat.XPos++;
            }
        }
        virtual public void Draw() { }
        ~GameObject()
        {
        }
    }
    class Protagonist : GameObject
    {
        private int Start_Hp { get; }
        public Protagonist(int x, int y, int h)
        {
            ObjectCoordinat.XPos = x;
            ObjectCoordinat.YPos = y;
            Start_Hp = h;
            ObjectHitBox.Down = 2;
            ObjectHitBox.Up = 3;
            ObjectHitBox.Left = 9;
            ObjectHitBox.Right = 9;
        }
        public void React(ConsoleKey key)
        {
            if (key == ConsoleKey.W)
            {
                Move("Up");
            }
            else if (key == ConsoleKey.S)
            {
                Move("Down");
            }
            else if (key == ConsoleKey.A)
            {
                Move("Left");
            }
            else if (key == ConsoleKey.D)
            {
                Move("Right");
            }

        }
        public override void Draw()
        {   //                                  
            //             &                   /\ /\        
            //         <|=&&&=|>              /&|_|&\      
            //             &            /\   /&&&&&&&\   /\
            //                          ||==|&&&&@&&&&|==|| 
            //                          \/   \&&&&&&&/   \/
            //                                \&&&&&/      
            //                                 

            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos - 3);
            Console.Write("       /\\ /\\       ");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos - 2);
            Console.Write("      /&|_|&\\      ");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos - 1);
            Console.Write("/\\   /&&&&&&&\\   /\\");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos);
            Console.Write("||==|&&&&@&&&&|==||");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos + 1);
            Console.Write("\\/   \\&&&&&&&/   \\/");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 9, ObjectCoordinat.YPos + 2);
            Console.Write("      \\&&&&&/      ");
        }
    }
    class Enemy : GameObject
    {
        public Enemy() { }
        public Enemy(int x, int y)
        {
            ObjectCoordinat.XPos = x;
            ObjectCoordinat.YPos = y;
        }
        /* public void Move(string Way, int wigth_limit, int high_limit)
         {
             switch (Way)
             {
                 case "Up":
                     {
                         if (ObjectCoordinat.YPos > 0)
                             ObjectCoordinat.YPos--;
                         break;
                     }
                 case "Down":
                     {
                         if (ObjectCoordinat.YPos < high_limit - 1)
                             ObjectCoordinat.YPos++;
                         break;
                     }
                 case "Right":
                     {
                         if (ObjectCoordinat.XPos < wigth_limit - 1)
                             ObjectCoordinat.XPos++;
                         break;
                     }
                 case "Left":
                     {
                         if (ObjectCoordinat.XPos > 0)
                             ObjectCoordinat.XPos--;
                         break;
                     }
             }
         }*/
        public override void Draw()
        {
            //                  _ _ 
            //                 / \ \
            //                 | |=|
            //                 \_/_/
            Console.SetCursorPosition(ObjectCoordinat.XPos - 2, ObjectCoordinat.YPos - 2);
            Console.Write(" _ _ ");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 2, ObjectCoordinat.YPos - 1);
            Console.Write("/ \\ \\");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 2, ObjectCoordinat.YPos - 0);
            Console.Write("| |=|");
            Console.SetCursorPosition(ObjectCoordinat.XPos - 2, ObjectCoordinat.YPos + 1);
            Console.Write("\\_/_/");

        }
    }
    class Settings
    {
        public int console_high_size { get; set; }
        public int console_wigth_size { get; set; }
        public int start_hp { get; set; }
        public int difficult { get; set; }
        public int count_of_enemy { get; set; }
        public HitBox Terrain_HitBox;
        public Settings() { }
        public void SetHitBox(int up, int down, int right, int left)
        {
            Terrain_HitBox.Down = down;
            Terrain_HitBox.Up = up;
            Terrain_HitBox.Left = left;
            Terrain_HitBox.Right = right;
        }
    }
    static class Game
    {
        private static List<Enemy> Enemys;
        private static Protagonist MainHero;
        private static Settings CurrentSetting;
        private static Random GameRandomiser;
        private static Surface GameSurface;
        static Game()
        {
            GameRandomiser = new Random();
            GameSurface = new Surface
                (
                CurrentSetting.console_wigth_size - (CurrentSetting.Terrain_HitBox.Right + CurrentSetting.Terrain_HitBox.Left),
                CurrentSetting.console_high_size - (CurrentSetting.Terrain_HitBox.Up + CurrentSetting.Terrain_HitBox.Down)
                );
        }
        public static void SetSettings(Settings sett)
        {
            CurrentSetting = sett;
        }
        public static void SetMainHero(Protagonist prtg)
        {
            MainHero = prtg;
        }
        public static void SetEnemys(List<Enemy> enem)
        {
            Enemys = enem;
        }
        static private string TransformValueIntoWay(int value)
        {
            switch (value)
            {
                case 0:
                    return "Up";
                case 1:
                    return "Right";
                case 2:
                    return "Down";
                case 3:
                    return "Left";
                default:
                    return "None";
            }
        }
        static void Show_Frame()
        {
            DrawTerrain();
            MainHero.Draw();
            for (int i = 0; i < Enemys.Count(); i++)
            {
                Enemys[i].Draw();
            }
        }
        private static void SpawnEnemy(Coordinates spawn_coord)
        {
            Enemys.Add(new Enemy(spawn_coord.XPos, spawn_coord.YPos));
        }
        private static void SpawnEnemy(int x, int y)
        {
            Enemys.Add(new Enemy(x, y));
        }
        public static void SpawnEnemy()
        {
            int Rand_Num_X = GameRandomiser.Next(2, CurrentSetting.console_wigth_size - 2), Rand_Num_Y = GameRandomiser.Next(2, CurrentSetting.console_high_size - 3);
            SpawnEnemy(Rand_Num_X, Rand_Num_Y);
        }
        private static void DrawTerrain()
        {
            for (int i = 0; i < CurrentSetting.console_wigth_size; i++)
            {
                Console.Write('_');
            }
            Console.SetCursorPosition(0, 1);
            Console.Write('|');
            for (int i = 0; i < CurrentSetting.console_wigth_size - 2; i++)
            {
                Console.Write('_');
            }
            Console.Write('|');
            Console.SetCursorPosition(0, 2);
            for (int i = 2; i < CurrentSetting.console_high_size - 1; i++)
            {
                Console.Write("||");
                Console.SetCursorPosition(CurrentSetting.console_wigth_size - 2, i);
                Console.Write("||");
            }
            Console.SetCursorPosition(0, CurrentSetting.console_high_size - 3);
            Console.Write('|');
            for (int i = 1; i < CurrentSetting.console_wigth_size - 2; i++)
            {
                Console.Write('_');
            }
            Console.Write("||");
            Console.SetCursorPosition(0, CurrentSetting.console_high_size - 2);
            for (int i = 0; i < CurrentSetting.console_wigth_size; i++)
            {
                Console.Write('_');
            }
        }
        private static void ControlMainHero()
        {
            Console.SetCursorPosition(MainHero.ReturnXPos(), MainHero.ReturnYPos());
            ConsoleKey MainHeroWay = Console.ReadKey(true).Key;
            if ((MainHeroWay == ConsoleKey.W && MainHero.ReturnYPos() - MainHero.ObjectHitBox.Up > CurrentSetting.Terrain_HitBox.Up) ||
                (MainHeroWay == ConsoleKey.S && MainHero.ReturnYPos() + MainHero.ObjectHitBox.Down < CurrentSetting.console_high_size - CurrentSetting.Terrain_HitBox.Down) ||
                (MainHeroWay == ConsoleKey.D && MainHero.ReturnXPos() + MainHero.ObjectHitBox.Right < CurrentSetting.console_wigth_size - CurrentSetting.Terrain_HitBox.Right - 1) ||
                (MainHeroWay == ConsoleKey.A && MainHero.ReturnXPos() - MainHero.ObjectHitBox.Left > CurrentSetting.Terrain_HitBox.Left))
                MainHero.React(MainHeroWay);
        }
        public static void StartGame()
        {
            if (MainHero == null)
            {
                MainHero = new Protagonist(CurrentSetting.console_wigth_size / 2, CurrentSetting.console_high_size / 2, CurrentSetting.start_hp);
            }
            do
            {
                Show_Frame();
                ControlMainHero();
                Thread.Sleep(50);

                SpawnEnemy(CurrentSetting.console_wigth_size / 2 - 10, CurrentSetting.console_high_size / 2 - 10);
                Console.Clear();
            } while (true);
        }
    }
}

