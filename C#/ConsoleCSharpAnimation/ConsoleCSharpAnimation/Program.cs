using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ConsoleCSharpAnimation
{
    class Program
    {

        static class SnowRandomizer
        {
            static Random randomizer;
            static List<bool> bool_list;
            static bool[] false_elements;
            static bool[] true_elements;
            static SnowRandomizer()
            {
                bool_list = new List<bool>();
                randomizer = new Random();
            }
           static public bool Generate(int percent_chance)
            {
                true_elements  = new bool[percent_chance];
                for (int i = 0; i < percent_chance; i++)
                {
                    true_elements[i] = true;
                }
                false_elements = new bool[100 - percent_chance];
                for (int i = 0; i < 100 - percent_chance; i++)
                {
                    false_elements[i] = false;
                }
                bool_list.AddRange(true_elements);
                bool_list.AddRange(false_elements);
                int random_num = randomizer.Next(0, 100);
                bool result = bool_list[random_num];
                bool_list.Clear();
                return result;
            }
        }
        static void Main(string[] args)
        {
            Console.SetBufferSize(200, 50);
            Console.SetWindowSize(200, 50);
            // Console.BackgroundColor = ConsoleColor.Blue;
            List<string> SnowStack = new List<string>(Console.BufferHeight);
            string line;
            do
            {
                line = "";
                for (int i = 0; i < Console.BufferWidth; i++)
                {
                    if (SnowRandomizer.Generate(10) == true)
                        line += '*';
                    else
                        line += ' ';
                }
                if(SnowStack.Count==SnowStack.Capacity)
                {
                    SnowStack.RemoveAt(0);
                }
                SnowStack.Add(line);
                for (int i = SnowStack.Count-1; i > 0; i--)
                {
                    Console.Write(SnowStack[i]);
                }
                Thread.Sleep(50);
                Console.Clear();
            } while (true);

        }
    }
}
