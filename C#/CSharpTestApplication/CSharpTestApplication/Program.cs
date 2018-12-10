using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Math;
using Basic_Classes;
using System.Reflection;
using System.IO;
using System.Runtime.Remoting.Contexts;
using System.Threading;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
namespace CSharpTestApplication
{
    [Synchronization]
    class SpecialClass : ContextBoundObject
    {
        public SpecialClass()
        {
            Context ctx = Thread.CurrentContext;
            Console.WriteLine("{0} object in context {1}", ToString(), ctx.ContextID);
            foreach (IContextProperty item in ctx.ContextProperties)
            {
                Console.WriteLine("->Current Context Propertie: {0}", item.Name);
            }
        }
    }
    class NotSpecialClass
    {
        public NotSpecialClass()
        {
            Context ctx = Thread.CurrentContext;
            Console.WriteLine("{0} object in context {1}", ToString(), ctx.ContextID);
            foreach (IContextProperty item in ctx.ContextProperties)
            {
                Console.WriteLine("->Current Context Propertie: {0}", item.Name);
            }
        }
    }
    class Node
    {
        public double value;
        public Node next;
        public Node() { }
        public Node(double val)
        {
            value = val;
            next = new Node();
        }
    }
    class List
    {
        Node start_node;
        int size;
        public List() { }
        public void Add(double val)
        {
            if (start_node == null)
            {
                start_node = new Node(val);
            }
            else
            {
                Node temp = start_node;
                for (int i = 0; i < size; i++)
                {
                    temp = temp.next;
                }
                temp = new Node(val);
            }
            size++;
        }
        public void Show()
        {
            Node temp = start_node;
            Console.Write(temp.value + "->");
            for (int i = 0; i < size - 1; i++)
            {
                temp = temp.next;
                if (i == size - 1)
                {
                    Console.Write(temp.value);
                }
                else
                {
                    Console.Write(temp.value + "->");
                }
            }
        }
    }
    class Detector
    {
        string Name;
        public Detector() { }
        public Detector(string name)
        {
            Name = name;
        }
        public void React(string sound)
        {
            if (sound == "Mrrr")
            {
                Console.WriteLine("Detector {0} has heared Mrrrr", Name);
            }
            else if (sound == "Meov")
            {
                Console.WriteLine("Detector {0} has heared Meov", Name);
            }
        }
    }
    [Serializable, Obsolete("Use Horse")]
    class Motorcycle
    {
        [NonSerialized]
        double speed;
        string model;

    }
    [Serializable]
    class SerializableClassCat
    {
        public string PetName;
        public int age;
        public SerializableClassCat() { }

    }
    [Serializable]
    class House
    {
        public SerializableClassCat HomeCat = new SerializableClassCat();
        public string adress;
    }
    [Serializable]
    class Flat : House
    {
        public double square;
        public override string ToString()
        {
            return string.Format("Adress: {0}, square: {1}, cat name: {2}, cat age: {3}", adress, square, HomeCat.PetName, HomeCat.age);
        }
    }

    class Program
    {
        private static object threadLock = new object();
        static void WaitFunc()
        {
            lock (threadLock)
            {
                double timer = 0;
                for (int i = 0; i < 10; i++)
                {
                    Console.Write("{0} ", timer);
                    timer += 1;
                    Thread.Sleep(1000);
                }
            }
        }
        static bool criterium(double value)
        {
            if (value % 2 == 0)
            {
                return true;
            }
            else return false;
        }
        static double factorial(double value)
        {
            double res = 1;
            for (int i = 1; i <= value; i++)
            {
                res *= i;
            }
            return res;
        }
        static double Combiantion(double less, double more)
        {
            return factorial(more) / (factorial(less) * factorial(more - less));
        }
        static void ListMethods(Type t)
        {
            try
            {
                var class_fields = from item in t.GetFields() select item.Name;
                Console.WriteLine("Fields");
                foreach (var item in class_fields)
                {
                    Console.WriteLine("->{0}", item);
                }
            }
            catch { }


            try
            {
                var class_methods = from item in t.GetMethods() select item.Name;
                Console.WriteLine("Methods");
                foreach (var item in class_methods)
                {
                    Console.WriteLine("->{0}", item);
                }
            }
            catch { }

            try
            {
                var class_properties = from item in t.GetProperties() select item.Name;
                Console.WriteLine("Properties");
                foreach (var item in class_properties)
                {
                    Console.WriteLine("->{0}", item);
                }
            }
            catch { }
        }
        static void DisplayTypeInAsm(Assembly asm)
        {
            Console.WriteLine("->{0}", asm.FullName);
            var types = from item in asm.GetTypes() select item;
            foreach (var item in types)
            {
                Console.WriteLine("Type: {0}", item);
            }
        }
        static void UsingAttriutesInEarlyBinding()
        {
            Type t = typeof(Mouse);
            var customAttriutes = from item in t.GetCustomAttributes(false) where item is PetDescriptionAttribute select item;
            foreach (PetDescriptionAttribute item in customAttriutes)
            {
                Console.WriteLine("-> {0}", item.Description);
            }
        }
        static void UsingAttriutesInLateBinding()
        {
            try
            {
                Assembly asm = Assembly.LoadFrom(@"F:\Visual Studio Projects\Libraries\FirstClassLibrary\FirstClassLibrary\bin\Debug\FirstClassLibrary.dll");
                Type pet_desc = asm.GetType("Basic_Classes.PetDescriptionAttribute");
                PropertyInfo propDesc = pet_desc.GetProperty("Description");
                Type[] type_in_assembly = asm.GetTypes();
                foreach (Type item in type_in_assembly)
                {
                    var custAtrr = from selected_item in item.GetCustomAttributes(pet_desc, false) select selected_item;
                    foreach (var ca in custAtrr)
                    {
                        Console.WriteLine("-> {0}: {1}", item.Name, propDesc.GetValue(ca, null));
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public delegate void DetectorDynamicReact(string sound);
        static void DynamicLateBinding(Assembly asm)
        {

            try
            {
                Type catType = asm.GetType("Basic_Classes.Cat");
                dynamic CatObject = Activator.CreateInstance(catType);
                Detector det1 = new Detector("First");
                //CatObject.Sound += det1.React;
                //CatObject.Sound +=new DetectorDynamicReact(det1.React);
                CatObject.Caress(10);
                Console.WriteLine("Done");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        static void WorkWithDomain(AppDomain TargetDomain)
        {
            Console.WriteLine("->Name: {0}\n->ID: {1}\n->Is Default: {2}\n->Base directory: {3}",
                TargetDomain.FriendlyName, TargetDomain.Id, TargetDomain.IsDefaultAppDomain(), TargetDomain.BaseDirectory);
            Assembly[] AssembliesInDomain = TargetDomain.GetAssemblies();
            foreach (Assembly item in AssembliesInDomain)
            {
                Console.WriteLine("->Name: {0}", item.GetName().Name);
            }
            Console.WriteLine();
        }
        static void CreateNewAppDomain()
        {
            AppDomain newAD = AppDomain.CreateDomain("Second Domain");
            try
            {
                newAD.Load("FirstClassLibrary");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            WorkWithDomain(newAD);
            newAD.DomainUnload += (obj, arg) =>
            {
                AppDomain temp = (AppDomain)obj;
                Console.WriteLine("{0} was unloaded!", temp.FriendlyName);
            };
            AppDomain.Unload(newAD);
        }
        static int Add(int first, int second)
        {
            Console.WriteLine("Add() invoked on thread {0}", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(5000);
            Console.WriteLine("Add() finished his work!");
            return first + second;
        }
        public delegate int BinaryOp(int x, int y);
        static void WorkWithThread()
        {
            Console.WriteLine("WorkWithThread() invoked on thread {0}", Thread.CurrentThread.ManagedThreadId);
            BinaryOp testOperation = new BinaryOp(Add);
            IAsyncResult iftAR = testOperation.BeginInvoke(10, 10, null, null);
            double timer = 0;
            while (!iftAR.AsyncWaitHandle.WaitOne(100, true))
            {
                timer += 1;
                Console.Write("{0} ", timer);
            }
            Console.WriteLine("Doing more work in WorkWithThread()!");
            int answer = testOperation.EndInvoke(iftAR);
            Console.WriteLine("10 + 10 is {0}.", answer);
        }
        static void PrintTime(object state)
        {
            Console.WriteLine("Time is {0} now", DateTime.Now.ToLongTimeString());
        }
        static void WorkWithTimer()
        {
            TimerCallback timeCB = new TimerCallback(PrintTime);
            Timer t = new Timer(timeCB, null, 0, 1000);
            Console.WriteLine("Hit key to terminate...");
        }
        static void WorkWithDirectorieInfo()
        {
            try
            {
                DirectoryInfo dir1 = new DirectoryInfo(@"F:\Svyatoslav\ScreenShots");
                FileInfo[] FileInfoArray = (from item in dir1.GetFiles("*.jpg", SearchOption.AllDirectories) select item).ToArray();
                Console.WriteLine("Found {0} .jpg files\n", FileInfoArray.Length);
                foreach (FileInfo item in FileInfoArray)
                {
                    Console.WriteLine("File Name: {0}\nSize: {1}\nCreation Time: {2}\nAttributes: {3}\n", item.Name, item.Length, item.CreationTime, item.Attributes);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
        static void DirectoryWork()
        {
            string[] drives = Directory.GetLogicalDrives();
            Console.WriteLine("Drives on computer:");
            foreach (string item in drives)
            {
                Console.WriteLine("-> {0}", item);
            }
            try
            {
                Directory.Delete(@"F:\Svyatoslav\C# Test Directory\gerghedgh");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        static void DriveInfoWork()
        {
            DriveInfo[] myDrives = DriveInfo.GetDrives();
            foreach (DriveInfo item in myDrives)
            {
                Console.WriteLine("Name: {0}\n\tType: {1}", item.Name, item.DriveType);
                if (item.IsReady)
                {
                    Console.WriteLine("\tFree space: {0}\n\tFormat: {1}\n\tLabel: {2}", item.TotalFreeSpace, item.DriveFormat, item.VolumeLabel);
                }
            }
        }
        static void FileInfoWork()
        {
            string TestFileDirectory = @"F:\Svyatoslav\C# Test Directory\Temp.txt";
            string[] myTask = { "Study C#", "Study TIMS" };
            File.WriteAllLines(TestFileDirectory, myTask);
            foreach (string item in File.ReadAllLines(TestFileDirectory))
            {
                Console.WriteLine("TODO: {0}", item);
            }
        }
        static void WorkWithFileStream()
        {
            string TestFileDirectory = @"F:\Svyatoslav\C# Test Directory\Temp.dat";
            using (FileStream testFileStream = File.Open(TestFileDirectory, FileMode.Create))
            {
                string Message = "Fuck You";
                byte[] MessageInByte = Encoding.Default.GetBytes(Message);
                Console.WriteLine("Write");
                testFileStream.Write(MessageInByte, 0, MessageInByte.Length);
                testFileStream.Position = 0;
                Console.WriteLine("Now read");
                byte[] ByteFromFile = new byte[MessageInByte.Length];
                for (int i = 0; i < MessageInByte.Length; i++)
                {
                    ByteFromFile[i] = (byte)testFileStream.ReadByte();
                    Console.Write(ByteFromFile[i]);
                }
                Console.WriteLine();
                Console.WriteLine("Now Decoded");
                Console.WriteLine(Encoding.Default.GetString(ByteFromFile));
            }
        }
        static void StreamWrite()
        {
            string TestFileDirectory = @"F:\Svyatoslav\C# Test Directory\Temp.txt";
            using (StreamWriter TestWiter = File.CreateText(TestFileDirectory))
            {
                TestWiter.WriteLine("Hello");
                TestWiter.WriteLine("Fucking World");
            }
        }
        static void StreamRead()
        {
            string TestFileDirectory = @"F:\Svyatoslav\C# Test Directory\Temp.txt";
            using (StreamReader TestStreamReader = File.OpenText(TestFileDirectory))
            {
                string input = null;
                while ((input = TestStreamReader.ReadLine()) != null)
                {
                    Console.WriteLine(input);
                }
            }
        }
        static void WorkWithStringWriterAndReader()
        {
            using (StringWriter strWriter = new StringWriter())
            {
                strWriter.WriteLine("Hello fucking world");
                Console.WriteLine(strWriter);
            }
        }
        static void BinaryReaderAndWriter(string FileDirectory)
        {
            FileInfo TestFileInfo = new FileInfo(FileDirectory);
            using (BinaryWriter bw = new BinaryWriter(TestFileInfo.OpenWrite()))
            {
                Console.WriteLine("Base stream is: {0}", bw.BaseStream);
                object[] arr = new object[] { 55.66, 11, "lolo" };
                bw.Write((double)arr[0]);
                bw.Write((int)arr[1]);
                bw.Write((string)arr[2]);
            }
            Console.WriteLine("Done");
            Console.WriteLine("Now read");
            using (BinaryReader br = new BinaryReader(TestFileInfo.OpenRead()))
            {
                Console.WriteLine(br.ReadDouble());
                Console.WriteLine(br.ReadInt32());
                Console.WriteLine(br.ReadString());
            }
            Console.WriteLine("Done");
        }
        static void WorkFileSystemWatcher(string FileDirectory)
        {
            FileSystemWatcher watcher = new FileSystemWatcher();
            try
            {
                watcher.Path = FileDirectory;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }
            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite | NotifyFilters.FileName | NotifyFilters.DirectoryName;
            watcher.Filter = "*.txt";
            watcher.Changed += new FileSystemEventHandler(OnChange);
            watcher.Deleted += new FileSystemEventHandler(OnChange);
            watcher.Created += new FileSystemEventHandler(OnChange);
            watcher.Renamed += new RenamedEventHandler(OnReamed);
            while (Console.Read() != 'q') ;
        }
        private static void OnReamed(object sender, RenamedEventArgs e)
        {
            Console.WriteLine("File: {0} renamed to {1}", e.OldFullPath, e.FullPath);
        }
        private static void OnChange(object sender, FileSystemEventArgs e)
        {
            Console.WriteLine("File: {0} {1}!", e.FullPath, e.ChangeType);
        }
        static void WorkWithSerializableClass()
        {
            SerializableClassCat FirstCat = new SerializableClassCat();
            FirstCat.PetName = "Molly";
            FirstCat.age = 12;
            BinaryFormatter binFormat = new BinaryFormatter();
            using (Stream fStream = new FileStream(@"F:\Svyatoslav\C# Test Directory\Temp1.dat", FileMode.Create, FileAccess.Write, FileShare.None))
            {
                binFormat.Serialize(fStream, FirstCat);
            }
        }
        static void SerializableConfigure()
        {

            Flat flat1 = new Flat();
            flat1.square = 12;
            flat1.adress = "wtf";
            flat1.HomeCat = new SerializableClassCat();
            flat1.HomeCat.age = 12;
            flat1.HomeCat.PetName = "Puffy";
            #region Binary Save and Load
            //Console.WriteLine(flat1.ToString());
            //SaveAsBinary(flat1, @"F:\Svyatoslav\C# Test Directory\tempBinary.dat");
            //Flat flat2 = (Flat)LoadFromBinary(@"F:\Svyatoslav\C# Test Directory\tempBinary.dat");
            //Console.WriteLine(flat2.ToString());
            #endregion
            #region Soap Save and Load
            //Console.WriteLine(flat1.ToString());
            //SaveAsSoap(flat1, @"F:\Svyatoslav\C# Test Directory\tempSoap.dat");
            //Flat flat3 = (Flat)LoadFromSoap(@"F:\Svyatoslav\C# Test Directory\tempSoap.dat");
            //Console.WriteLine(flat3.ToString());
            #endregion
            Flat flat4 = new Flat();
            flat4.square = 5;
            flat4.adress = "wtfisgon";
            flat4.HomeCat = new SerializableClassCat();
            flat4.HomeCat.age = 2;
            flat4.HomeCat.PetName = "Lazy";
            List<Flat> FlatList = new List<Flat>();
            FlatList.Add(flat1);
            FlatList.Add(flat4);
            #region List saved binary
            foreach (Flat item in FlatList)
            {
                Console.WriteLine(item.ToString());
            }
            SaveAsBinary(FlatList, @"F:\Svyatoslav\C# Test Directory\tempBinaryList.dat");
            List<Flat> list2 = (List<Flat>)LoadFromBinary(@"F:\Svyatoslav\C# Test Directory\tempBinaryList.dat");
            foreach (Flat item in list2)
            {
                Console.WriteLine(item.ToString());
            }
            #endregion
        }
        static void SaveAsBinary(object objGraph, string fileName)
        {
            BinaryFormatter bf = new BinaryFormatter();
            using (Stream fs = new FileStream(fileName, FileMode.Create, FileAccess.Write, FileShare.None))
            {
                bf.Serialize(fs, objGraph);
            }
        }
        static object LoadFromBinary(string fileName)
        {
            BinaryFormatter bf = new BinaryFormatter();
            using (Stream fs = File.OpenRead(fileName))
            {
                return bf.Deserialize(fs);
            }
        }
        static void SaveAsSoap(object objGraph, string fileName)
        {
            SoapFormatter sf = new SoapFormatter();
            using (Stream fs = new FileStream(fileName, FileMode.Create, FileAccess.Write, FileShare.None))
            {
                sf.Serialize(fs, objGraph);
            }
        }
        static object LoadFromSoap(string fileName)
        {
            SoapFormatter sf = new SoapFormatter();
            using (Stream fs = File.OpenRead(fileName))
            {
                return sf.Deserialize(fs);
            }
        }
        static void Main(string[] args)
        {
            //Asin(Sqrt(Pow(Cos(f), 2) / (1 - Pow(Cos(f), 2))));
            int range = 100;
            double result = 0, arg;
            for (int i = 0; i < 100; i++)
            {
                arg = i;
                result = Asin(Sqrt(Pow(Cos(arg), 2) / (1 - Pow(Cos(arg), 2))));
                if (result <= 1 && result >= -1)
                {
                    Console.Write($"{arg} ");
                }
            }
            Console.WriteLine("Done!");
            Console.ReadLine();
        }
    }
}
