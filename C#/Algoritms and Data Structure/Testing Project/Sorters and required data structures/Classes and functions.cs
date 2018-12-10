using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Sorters_and_required_data_structures
{
    public class Branch
    {
        public int value;
        public Branch parent;
        public Branch left;
        public Branch right;
        public Branch(int val, Branch par) { value = val; parent = par; }
    }
    public class BinaryTree
    {
        Branch root;
        int size;
        public BinaryTree() { size = 0; }
        private void AddTo(Branch target, int val)
        {
            if (target.value > val)
            {
                if (target.left == null)
                {
                    target.left = new Branch(val, target);
                    size++;
                }
                else AddTo(target.left, val);
            }
            else if (target.value < val)
            {
                if (target.right == null)
                {
                    target.right = new Branch(val, target);
                    size++;
                }
                else AddTo(target.right, val);
            }
        }
        public void Add(int val)
        {
            if (root == null)
            {
                root = new Branch(val, null);
            }
            else
            {
                AddTo(root, val);
            }
        }
    }
    public class Pyramid
    {
        List<int> items;
        public Pyramid() { items = new List<int>(); }
        public void Add(int val)
        {
            items.Add(val);
            int i = items.Count - 1;
            int parent = (i - 1) / 2;
            while (i > 0 && items[parent] < items[i])
            {
                int temp = items[i];
                items[i] = items[parent];
                items[parent] = temp;
                i = parent;
                parent = (i - 1) / 2;
            }

        }
        private void Heapify(int i)
        {
            int leftChild;
            int rightChild;
            int largestChild;
            do
            {
                leftChild = 2 * i + 1;
                rightChild = 2 * i + 2;
                largestChild = i;
                if (leftChild < items.Count && items[leftChild] > items[largestChild])
                {
                    largestChild = leftChild;
                }
                if (rightChild < items.Count && items[rightChild] > items[largestChild])
                {
                    largestChild = rightChild;
                }
                if (largestChild == i)
                {
                    break;
                }
                int temp = items[i];
                items[i] = items[largestChild];
                items[largestChild] = temp;
                i = largestChild;
            } while (true);
        }
        private void BuiltHeap(int[] array)
        {
            items = array.ToList();
            for (int i = items.Count / 2; i >= 0; i--)
            {
                Heapify(i);
            }
        }
        private int GetMax()
        {
            int result = items[0];
            items[0] = items[items.Count - 1];
            items.RemoveAt(items.Count - 1);
            return result;
        }
        public void Sort(int[] array)
        {
            BuiltHeap(array);
            for (int i = array.Length - 1; i >= 0; i--)
            {
                array[i] = GetMax();
                Heapify(0);
            }
        }
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < items.Count; i++)
            {
                sb.AppendFormat($"{items[i]} ");
            }
            return sb.ToString();
        }
    }
    public static class BinarySearch
    {
        private static int binarySearch(int[] array, int value, int low, int high)
        {
            if (low > high) return -1;
            int middle = (low + high) / 2;
            if (value < array[middle])
            {
                return binarySearch(array, value, low, middle - 1);
            }
            else if (value > array[middle])
            {
                return binarySearch(array, value, middle + 1, high);
            }
            else return middle;
        }
        public static int Search(int[] array, int value)
        {
            return binarySearch(array, value, 0, array.Length - 1);
        }
    }
    public static class SortedFunc
    {
        public static void Mix(int[] array)
        {
            Random randomiser = new Random();
            int j;
            for (int i = 0; i < array.Length; i++)
            {
                j = randomiser.Next(0, array.Length - 1);
                Swap(ref array[i], ref array[j]);
            }
        }
        public static void Swap(ref int first, ref int second)
        {
            int temp = first;
            first = second;
            second = temp;
        }
        public static void Push(ref int[] array, int to, int from)
        {
            int temp = array[from];
            for (int i = from; i > to; i--)
            {
                array[i] = array[i - 1];
            }
            array[to] = temp;
        }
        public static void Test(Sorter TestSort, int[] put_array)
        {
            int[] array = new int[put_array.Length];
            Array.Copy(put_array, array, put_array.Length);
            Stopwatch Timer = new Stopwatch();
            Console.WriteLine("Testing {0}", TestSort.AlgName);
            Console.WriteLine("Star Testing: ");
            Timer.Start();
            TestSort.Sort(ref array);
            Timer.Stop();
            Console.WriteLine("End Testing");
            TimeSpan SpendTime = Timer.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            SpendTime.Hours, SpendTime.Minutes, SpendTime.Seconds,
            SpendTime.Milliseconds);
            Timer.Reset();
            Console.WriteLine("Result for {0} with {1} elements is {2}", TestSort.AlgName, array.Length, elapsedTime);
            Console.WriteLine();
        }
        public static void ShowArray(int[] array)
        {
            foreach (int element in array)
            {
                Console.Write($"{element} ");
            }
        }

    }
    public abstract class Sorter
    {
        protected string Name;
        public Sorter() { }
        abstract public void Sort(ref int[] array);
        public string AlgName
        {
            get
            {
                return Name;
            }
        }
    }
    public class BubbleSorter : Sorter
    {
        public BubbleSorter() { Name = "Bubble Sort"; }
        public override void Sort(ref int[] array)
        {
            double operations = 0;
            for (int i = 0; i < array.Length - 1; i++)
            {
                for (int j = 0; j < array.Length - 1 - i; j++)
                {
                    if (array[j] > array[j + 1])
                    {
                        SortedFunc.Swap(ref array[j], ref array[j + 1]);
                        operations += 10;
                    }
                    else
                    {
                        operations += 5;
                    }
                    operations += 2;
                }
                operations += 2;

            }

            Console.WriteLine($"Total operations are: {operations}");
        }
    }
    public class SelectionSorter : Sorter
    {
        public SelectionSorter() { Name = "Selection Sort"; }
        public override void Sort(ref int[] array)
        {
            int min_value, min_element;
            double operations = 0;
            for (int i = 0; i < array.Length - 1; i++)
            {
                min_element = i;
                min_value = array[i];
                operations += 3;
                for (int j = i; j < array.Length; j++)
                {
                    if (array[j] < min_value)
                    {
                        min_value = array[j];
                        min_element = j;
                        operations += 3;
                    }
                    operations += 4;
                }
                SortedFunc.Swap(ref array[i], ref array[min_element]);
                operations += 7;
            }

            Console.WriteLine($"Total operations: {operations}");
        }
    }
    public class InsertionSort : Sorter
    {
        public InsertionSort() { Name = "Insertion Sort"; }
        public override void Sort(ref int[] array)
        {
            int k;
            for (int i = 1; i < array.Length; i++)
            {
                if (array[i] < array[i - 1])
                {
                    k = i - 1;
                    do
                    {
                        if (k == 0 || array[k - 1] < array[i]) break;
                        k--;
                    } while (true);
                    SortedFunc.Push(ref array, k, i);
                }
            }
        }
    }
    public class HeapSorter : Sorter
    {
        Pyramid sortPyramid;
        public HeapSorter() { Name = "Heap Sorter"; sortPyramid = new Pyramid(); }
        public override void Sort(ref int[] array)
        {
            sortPyramid.Sort(array);
        }
    }
    public class MergeSorter : Sorter
    {
        public MergeSorter() { Name = "Merge Sort"; }
        private int[] Merge(int[] arr1, int[] arr2)
        {
            int a = 0, b = 0;
            int[] merged = new int[arr1.Length + arr2.Length];
            for (int i = 0; i < arr1.Length + arr2.Length; i++)
            {
                if (b < arr2.Length && a < arr1.Length)
                {
                    if (arr1[a] > arr2[b])
                    {
                        merged[i] = arr2[b++];
                    }
                    else
                    {
                        merged[i] = arr1[a++];
                    }
                }
                else
                {
                    if (b < arr2.Length)
                    {
                        merged[i] = arr2[b++];
                    }
                    else
                    {
                        merged[i] = arr1[a++];
                    }
                }
            }
            return merged;
        }
        private int[] MergeSort(int[] array)
        {
            if (array.Length == 1)
            {
                return array;
            }
            int middlePoint = array.Length / 2;
            return Merge(MergeSort(array.Take(middlePoint).ToArray()), MergeSort(array.Skip(middlePoint).ToArray()));
        }
        public override void Sort(ref int[] array)
        {
            array = MergeSort(array);
        }
    }
    public class QuickSorter : Sorter
    {
        public QuickSorter() { Name = "Quick Sort"; }
        public override void Sort(ref int[] array)
        {
            QuickSort(array, 0, array.Length - 1);
        }
        private void QuickSort(int[] array, long first, long last)
        {
            int medium = array[(last - first) / 2 + first];
            int temp;
            long i = first, j = last;
            while (i <= j)
            {
                while (array[i] < medium && i <= last) ++i;
                while (array[j] > medium && j >= first) --j;
                if (i <= j)
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    ++i; --j;
                }
            }
            if (j > first) QuickSort(array, first, j);
            if (i < last) QuickSort(array, i, last);
        }
    }
    public static class TestingFunctions
    {
        public static void FullArrayWithRandomNumbers(double[] arr, Random randomiser, int min, int max)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = randomiser.Next(min, max);
            }
        }
        public static void FullArrayWithIterationElements(int[] arr)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = i;
            }
        }
        public static void SmallAndLargeNumbersAddTest(int count, int smallRange, int largeRange)
        {
            double[] smallArr = new double[count];
            double[] largeArr = new double[count];
            double[] smallAddArr = new double[count];
            double[] largeAddArr = new double[count];
            Random testRandomiser = new Random();
            Stopwatch timer = new Stopwatch();
            FullArrayWithRandomNumbers(smallArr, testRandomiser, 0, smallRange);
            FullArrayWithRandomNumbers(largeArr, testRandomiser, largeRange / 2, largeRange);
            FullArrayWithRandomNumbers(smallAddArr, testRandomiser, 0, smallRange);
            FullArrayWithRandomNumbers(largeAddArr, testRandomiser, largeRange / 2, largeRange);
            timer.Start();
            for (int i = 0; i < count; i++)
            {
                smallArr[i] += smallAddArr[i];
            }
            timer.Stop();
            TimeSpan spendTimeForSmall = timer.Elapsed;
            string elapsedTimeForSmall = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            spendTimeForSmall.Hours, spendTimeForSmall.Minutes, spendTimeForSmall.Seconds,
            spendTimeForSmall.Milliseconds);
            Console.WriteLine($"Result for small numbers with {count} elements is {elapsedTimeForSmall}");
            timer.Reset();
            timer.Start();
            for (int i = 0; i < count; i++)
            {
                largeArr[i] += largeAddArr[i];
            }
            timer.Stop();
            TimeSpan spendTimeForLarge = timer.Elapsed;
            string elapsedTimeForLarge = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            spendTimeForLarge.Hours, spendTimeForLarge.Minutes, spendTimeForLarge.Seconds,
            spendTimeForLarge.Milliseconds);
            Console.WriteLine($"Result for large numbers with {count} elements is {elapsedTimeForLarge}");
            timer.Reset();
        }
    }
}
