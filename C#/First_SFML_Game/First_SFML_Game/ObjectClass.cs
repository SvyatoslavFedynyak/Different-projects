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
     class BaseObject
    {
        protected Sprite ObjectSprite;
        Coordinates ObjectPosition;
        public BaseObject() { }
    }
    class MainHero : BaseObject
    {
        public MainHero() { }
        public MainHero(Sprite objsprite)
        {
            ObjectSprite = objsprite;
        }
    }
    class Sprite
    {
        string Directional;
        string Name;
        protected Texture SpriteTexture;
        public Sprite() { }
        public Sprite(string Dirr, string name)
        {
            Directional = Dirr;
            Name = name;
            SpriteTexture = new Texture(Directional+name);
        }
    }
}
