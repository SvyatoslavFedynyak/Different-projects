using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using Basic;
using Sorters_and_required_data_structures;
namespace Testing_Project
{

    class Program
    {
        static void Main(string[] args)
        {
            Random Randomizer = new Random();
            Console.WriteLine("Enter NUMBER OF ELEMNTS:");
            int size = Convert.ToInt32(Console.ReadLine());
            //int[] Array = new int[size];
            TestingFunctions.SmallAndLargeNumbersAddTest(size, 10, 100000000);
            int[] testArr = new int[size];
            TestingFunctions.FullArrayWithIterationElements(testArr);
            //Random randomiser = new Random();
            int testValue = 51;
            Console.WriteLine(testValue == BinarySearch.Search(testArr, testValue));
            #region Random generate
            //for (int i = 0; i < Array.Length; i++)
            //{
            //    Array[i] = Randomizer.Next(0, 100);
            //} 
            #endregion
            #region Unique Elements
            //for (int i = 0; i < Array.Length; i++)
            //{
            //    Array[i] = i;
            //}
            //SortedFunc.Mix(Array);
            #endregion
            #region Testing
            //Test(bubblesort, Array);
            //Test(selectionsorter, Array);
            //Test(insertionsorter, Array);
            //Test(heapsorter, Array);
            //Test(mergesorter, Array);
            //Test(quicksorter, Array);
            #endregion
            Console.ReadLine();
        }
    }
}
