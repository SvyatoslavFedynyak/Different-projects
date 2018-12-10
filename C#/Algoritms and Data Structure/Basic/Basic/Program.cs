using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;

namespace Basic
{
    class Node
    {
        public double value;
        public Node next;
        Node() { }
        public Node(double value_)
        {
            value = value_;
        }

    }
    class OwnList
    {
        Node head;
        int size;
        public OwnList() { }
        public void Add(double val)
        {
            if (head == null)
            {
                head = new Node(val);
            }
            else
            {
                Node temp = head;
                while (temp.next != null)
                {
                    temp = temp.next;
                }
                temp.next = new Node(val);
            }
            size++;
        }
        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            if (size == 0)
            {
                return "List is empty";
            }
            else
            {
                Node temp = head;
                result.AppendFormat($"{temp.value}");
                while (temp.next != null)
                {
                    result.AppendFormat($"->{temp.next.value}");
                    temp = temp.next;
                }
            }
            return result.ToString();
        }
    }
    class Pyramid
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
            for (int i = array.Length -1 ; i >=0; i--)
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
    class Program
    {
        static void TestFunc(double[] test)
        {
            for (int i = 0; i < test.Length; i++)
            {
                test[i] += 100;
            }
        }
        static void Main(string[] args)
        {
            #region Time Tester
            //Stopwatch timer1 = new Stopwatch();
            //double[] test = new double[10000000];
            //for (int i = 0; i < test.Length; i++) test[i] = i;
            //Console.WriteLine("Timer started");
            //timer1.Start();
            //TestFunc(test);
            //timer1.Stop();
            //TimeSpan ts = timer1.Elapsed;
            //Console.WriteLine($"Total time: {ts.Minutes}:{ts.Seconds}:{ts.Milliseconds}"); 
            #endregion

            Console.ReadLine();
        }
    }
}
