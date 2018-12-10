using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using SFML.Graphics;
using SFML.System;
using SFML.Window;


namespace SeaWar
{
    struct Sprite
    {
        Texture SpriteTexture;
        Sprite(Texture text)
        { 
            SpriteTexture = text;
        }
    }
    struct Coordinates
    {
        public int X, Y;
        public Coordinates(int x, int y)
        {
            X = x; Y = y;
        }
    }
    class Point
    {
        public Sprite Point_Sprite;
        public Coordinates Point_Coordinates;
        public Ship Occupied_Ship;
        public bool ShipPresent;
        public bool Shoted;
        public bool NearSheepPresent;
        public Point()
        {

        }
        public Point(int x, int y)
        {
            Point_Coordinates = new Coordinates(x, y);
            Point_Sprite = new Sprite();
        }
        public void Draw()
        {
            if (ShipPresent == false && Shoted == false)
            {
                Console.SetCursorPosition(Point_Coordinates.X, Point_Coordinates.Y);
                Console.BackgroundColor = ConsoleColor.Blue;
                Console.Write(" ");
            }
            else if (ShipPresent == true && Shoted == false)
            {
                Console.SetCursorPosition(Point_Coordinates.X, Point_Coordinates.Y);
                Console.BackgroundColor = ConsoleColor.Gray;
                Console.Write(" ");
            }
            else if (ShipPresent == true && Shoted == true)
            {
                Console.SetCursorPosition(Point_Coordinates.X, Point_Coordinates.Y);
                Console.BackgroundColor = ConsoleColor.Gray;
                Console.Write("x");
            }
            else if (ShipPresent == false && Shoted == true)
            {
                Console.SetCursorPosition(Point_Coordinates.X, Point_Coordinates.Y);
                Console.BackgroundColor = ConsoleColor.Blue;
                Console.Write("·");
            }
        }
    }
    class Ship
    {
        public Point[] Ship_Points;
        public int size;
        public bool Vertical;
        bool Dead;
        public Ship() { }
        public Ship(Point[] coord)
        {
            size = coord.Length;
            if (coord[1].Point_Coordinates.X > coord[0].Point_Coordinates.X) Vertical = false;
            else Vertical = true;
            Ship_Points = new Point[size];
            for (int i = 0; i < size; i++)
            {
                Ship_Points[i] = coord[i];
                coord[i].ShipPresent = true;
                coord[i].Occupied_Ship = this;
            }
        }
    }
    class Field
    {
        static Random Randomiser;
        public Point[,] Surface;
        public Ship[] Shipes;
        public int surface_size;
        private int Ship_Capacity;
        public Field() { }
        public Field(int s)
        {
            surface_size = s;
            Surface = new Point[surface_size, surface_size];
            for (int i = 0; i < surface_size; i++)
            {
                for (int j = 0; j < surface_size; j++)
                {
                    Surface[i, j] = new Point(i, j);
                }
            }
            Shipes = new Ship[6];
            Ship_Capacity = 0;
            Randomiser = new Random();
        }
        static bool IntToBool(int a)
        {
            if (a == 0) return false;
            else return true;
        }
        public void Draw()
        {
            for (int i = 0; i < surface_size; i++)
            {
                for (int j = 0; j < surface_size; j++)
                {
                    Surface[i, j].Draw();
                }
            }
        }
        private void OverrideShip(Ship ship)
        {
            int x, y;
            for (int i = 0; i < ship.size; i++)
            {
                x = ship.Ship_Points[i].Point_Coordinates.X;
                y = ship.Ship_Points[i].Point_Coordinates.Y;
                if (ship.Vertical == false)
                {
                    Surface[x, y].ShipPresent = true;
                    //по бокам
                    if (i == 0 && x > 0) Surface[x - 1, y].NearSheepPresent = true;
                    if (i == ship.size-1 && x < this.surface_size - 1) Surface[x + 1, y].NearSheepPresent = true;
                    //зверху, знизу
                    if (y > 0) Surface[x, y - 1].NearSheepPresent = true;
                    if (y < this.surface_size - 1) Surface[x, y + 1].NearSheepPresent = true;
                    //по кутам
                    if (i == 0 && y > 0 && x > 0) Surface[x - 1, y - 1].NearSheepPresent = true;
                    if (i == 0 && y < this.surface_size - 1 && x > 0) Surface[x - 1, y + 1].NearSheepPresent = true;
                    if (i == ship.size-1 && y > 0 && x < this.surface_size - 1) Surface[x + 1, y - 1].NearSheepPresent = true;
                    if (i == ship.size-1 && y < this.surface_size - 1 && x < this.surface_size - 1) Surface[x + 1, y + 1].NearSheepPresent = true;
                }
                else
                {
                    Surface[x, y].ShipPresent = true;
                    //зверху, знизу
                    if (i == 0 && y > 0) Surface[x, y - 1].NearSheepPresent = true;
                    if (i == ship.size-1 && y < this.surface_size - 1) Surface[x, y + 1].NearSheepPresent = true;
                    //по бокам
                    if (x > 0) Surface[x - 1, y].NearSheepPresent = true;
                    if (x < this.surface_size - 1) Surface[x + 1, y].NearSheepPresent = true;
                    //по кутам
                    if (i == 0 && y > 0 && x > 0) Surface[x - 1, y - 1].NearSheepPresent = true;
                    if (i == ship.size-1 && y < this.surface_size - 1 && x > 0) Surface[x - 1, y + 1].NearSheepPresent = true;
                    if (i == 0 && y > 0 && x < this.surface_size - 1) Surface[x + 1, y - 1].NearSheepPresent = true;
                    if (i == ship.size-1 && y < this.surface_size - 1 && x < this.surface_size - 1) Surface[x + 1, y + 1].NearSheepPresent = true;
                }
            }
        }
        public void AddOneShip(Point[] coord)
        {
            if (Ship_Capacity <= 7)
            {
                Shipes[Ship_Capacity] = new Ship(coord);
                OverrideShip(Shipes[Ship_Capacity]);
                Ship_Capacity++;
            }

        }
        private Coordinates FindPlace(bool vert, int size)
        {
            int sx, sy, currx, curry;
            bool place_finded;
            do
            {
                //find place
                if (vert == true)
                {
                    sx = Randomiser.Next(0, surface_size);
                    sy = Randomiser.Next(0, surface_size - 4);
                }
                else
                {
                    sx = Randomiser.Next(0, surface_size - 4);
                    sy = Randomiser.Next(0, surface_size);
                }
                //start checking
                currx = sx;
                curry = sy;
                place_finded = true;
                for (int i = 0; i < size; i++)
                {
                    if (Surface[currx, curry].NearSheepPresent || Surface[currx, curry].ShipPresent)
                    {
                        place_finded = false;
                        break;
                    }
                    if (vert == true)
                    {
                        if (Surface[currx, curry + i].NearSheepPresent || Surface[currx, curry + i].ShipPresent)
                        {
                            place_finded = false;
                            break;
                        }
                    }
                    else
                    {
                        if (Surface[currx+i, curry].NearSheepPresent || Surface[currx+i, curry].ShipPresent)
                        {
                            place_finded = false;
                            break;
                        }
                    }
                }
            } while (place_finded==false);
            Coordinates result = new Coordinates(currx, curry);
            return result;
        }
        private bool GetBool()
        {
            int int_bool;
            int_bool = Randomiser.Next(0, 2);
            if (int_bool == 0) return false;
            else return true;
        }
        public void AddShipes()
        {
            Point[] temp;
            bool vert;
            Coordinates start_coord;
            //add 1 4-bort ship
            vert = GetBool();
            temp = new Point[4];
            start_coord = FindPlace(vert, 4);
            for (int i = 0; i < 4; i++)
            {
                if (vert == true)
                {
                    temp[i] = new Point(start_coord.X, start_coord.Y + i);
                }
                else
                {
                    temp[i] = new Point(start_coord.X + i, start_coord.Y);
                }
            }
            AddOneShip(temp);
            //add 2 3-bord ship
            for (int j = 0; j < 2; j++)
            {
                vert = GetBool();
                temp = new Point[3];
                start_coord = FindPlace(vert, 3);
                for (int i = 0; i < 3; i++)
                {
                    if (vert == true)
                    {
                        temp[i] = new Point(start_coord.X, start_coord.Y + i);
                    }
                    else
                    {
                        temp[i] = new Point(start_coord.X + i, start_coord.Y);
                    }
                }
                AddOneShip(temp);
            }
            //add 3 2-bord ship
            for (int j = 0; j < 3; j++)
            {
                vert = GetBool();
                temp = new Point[2];
                start_coord = FindPlace(vert, 2);
                for (int i = 0; i < 2; i++)
                {
                    if (vert == true)
                    {
                        temp[i] = new Point(start_coord.X, start_coord.Y + i);
                    }
                    else
                    {
                        temp[i] = new Point(start_coord.X + i, start_coord.Y);
                    }
                }
                AddOneShip(temp);
            }
        }
        public void Clear()
        {
            //for(int i=0; i<Shipes.Length;i++)
            //{
            //    Shipes[0] = null;
            //}
            //for(int i=0;i<surface_size;i++)
            //{
            //    for(int j=0;j<surface_size;j++)
            //    {
            //        Surface[i, j]=new Point[]
            //    }
            //}
            Surface = new Point[surface_size, surface_size];
            for (int i = 0; i < surface_size; i++)
            {
                for (int j = 0; j < surface_size; j++)
                {
                    Surface[i, j] = new Point(i, j);
                }
            }
            Shipes = new Ship[6];
            Ship_Capacity = 0;
        }
    }
    class Program
    {

        static void Main(string[] args)
        {
            Field field = new Field(10);
            do
            {
                field.AddShipes();
                field.Draw();
                Thread.Sleep(500);
                field.Clear();
            } while (true);

            Console.Read();
        }

    }
}


