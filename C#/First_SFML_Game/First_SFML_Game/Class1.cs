using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SFML.Window;
using SFML.System;
using SFML.Graphics;

namespace First_SFML_Game
{
    //Elements
    enum TileType
    {
        Default,
        Shoted_Empty,
        Ship,
        Shoted_Ship,
        Died_Ship
    }
    class Tile
    {
        TileType Tile_Type;
        Sprite Tile_Sprite;
        Coordinates Tile_Coordinates;
        TileType Type
        {
            set { Tile_Type = value; }
            get { return Tile_Type; }
        }
        Coordinates Coordinate
        {
            get { return Tile_Coordinates; }
            set { Tile_Coordinates = value; }
        }
        Sprite Sprite
        {
            set { Tile_Sprite = value; }
            get { return Tile_Sprite; }
        }
        Tile()
        {
            Tile_Sprite = new Sprite();
            Tile_Coordinates = new Coordinates();
        }
    }
    class Field
    {
        Tile[,] Game_Field;
        int size;
        Field() { }
        Field(int s)
        {
            size = s;
            Game_Field = new Tile[size, size];
        }
    }
    struct Coordinates
    {
       public int X, Y;
        Coordinates(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
    struct Resolution
    {
        public int Vertical;
        public int Horizontal;
        public Resolution(int hor, int vert)
        {
            Vertical = vert;
            Horizontal = hor;
        }
    }
    class Settings
    {
        private Resolution GameResolution;
        public Resolution Game_Resolution
        {
            get { return GameResolution; }
            set
            {
                if (value.Horizontal <= 2560 && value.Horizontal > 0 && value.Vertical <= 1080 && value.Vertical > 0)
                {
                    GameResolution = value;
                }
            }
        }
        public bool Vertical_Sync;
    }
    static class Game
    {
        static List<BaseObject> GameObjects;
        static string GameName;
        static Settings GameSettings;
        static RenderWindow window;
        static public Settings Game_Settings
        {
            set { GameSettings = value; }
            get { return GameSettings; }
        }
        static Game()
        {
            GameSettings = new Settings();
            GameObjects = new List<BaseObject>();
        }
        static void Win_Closed(object sender, EventArgs e)
        {
            window.Close();
        }
        public static string Name
        {
            set { GameName = value; }
            get { return GameName; }
        }
        public static void Add_Game_Object(BaseObject add_obj)
        {
            GameObjects.Add(add_obj);
        }
        public static void Start_Game()
        {
            window = new RenderWindow(new VideoMode((uint)GameSettings.Game_Resolution.Horizontal, (uint)GameSettings.Game_Resolution.Vertical), GameName);
            window.SetVerticalSyncEnabled(GameSettings.Vertical_Sync);

            window.Closed += Win_Closed;

            //загрузка обєктів



            while (window.IsOpen)
            {
                window.DispatchEvents();
                window.Clear(Color.White);

                //Draw here

                window.Display();
            }
        }
    }
    //Additional Functions


}

