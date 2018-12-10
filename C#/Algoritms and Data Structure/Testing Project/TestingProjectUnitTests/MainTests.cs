using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Sorters_and_required_data_structures;
using System.Text;

namespace TestingProjectUnitTests
{
    [TestClass]
    public class MainTests
    {
        Random randomiser = new Random();
        private int size = 100;
        [TestMethod]
        public void CorrectBubbleSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            BubbleSorter sorter = new BubbleSorter();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectSelectionSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            SelectionSorter sorter = new SelectionSorter();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectInsertionSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            InsertionSort sorter = new InsertionSort();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectMergeSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            MergeSorter sorter = new MergeSorter();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectHeapSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            HeapSorter sorter = new HeapSorter();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectQuickSortingWorkTest()
        {
            int[] defaultArray = new int[size];
            for (int i = 0; i < defaultArray.Length; i++)
            {
                defaultArray[i] = i;
            }
            int[] mixedArray = new int[size];
            Array.Copy(defaultArray, mixedArray, defaultArray.Length);
            SortedFunc.Mix(mixedArray);
            QuickSorter sorter = new QuickSorter();
            sorter.Sort(ref mixedArray);
            CollectionAssert.AreEqual(mixedArray, defaultArray);
        }
        [TestMethod]
        public void CorrectBinarySearchWork()
        {
            int[] testArr = new int[size];
            TestingFunctions.FullArrayWithIterationElements(testArr);
            Random randomiser = new Random();
            int testValue = randomiser.Next(size);
            Assert.AreEqual(testValue, BinarySearch.Search(testArr, testValue));
        }
    }
}
