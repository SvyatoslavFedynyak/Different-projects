using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using System.Threading;
using System.Net.Http;
using System.Net.Sockets;

namespace WebStudyConsoleAplication
{

    class Program
    {
        static void WorkWithBasicWeb()
        {
            #region IP
            IPAddress ip1 = new IPAddress(new byte[] { 45, 43, 34, 11 });
            Console.WriteLine(ip1.AddressFamily);
            IPAddress ip2 = IPAddress.Parse("[3EA0:FFFF:198A:E4A3:4FF2:54FA:41BC:8D31]");
            Console.WriteLine(ip2.AddressFamily);
            IPEndPoint EndPoint1 = new IPEndPoint(ip1, 222);
            #endregion
            #region URI
            Uri MyFacebook = new Uri("https://www.facebook.com/svyatoslav.fedynyak");
            Console.WriteLine(MyFacebook.Scheme);
            #endregion
            #region WebClient
            WebClient wb1 = new WebClient { Proxy = null };
            Uri uri1 = new Uri(@"https://ru.wikipedia.org/wiki/URI");
            Uri uri2 = new Uri(@"F:\FrontEnd\FirstPage.html");
            try
            {
                wb1.DownloadFile(uri1, @"F:\FrontEnd\temp.html");
                System.Diagnostics.Process.Start("temp.html");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            #endregion
        }
        async static void HttpClientWork(Uri FileUri)
        {
            string HTMLResult = await new HttpClient().GetStringAsync(FileUri);
            Console.WriteLine(HTMLResult);
        }
        static async void WebRequest(Uri FileUri)
        {
            await TaskRequestAsync(FileUri);
            Console.WriteLine("Gotcha!");
        }
        static Task TaskRequestAsync(Uri fileUri)
        {
            return Task.Run(() =>
            {
                Thread.Sleep(2000);
                WebClient RequestWebClient = new WebClient { Proxy = null };
                string LocalFile = "temp.html";
                RequestWebClient.DownloadFile(fileUri, LocalFile);
                System.Diagnostics.Process.Start(LocalFile);
            });

        }
        async static void WorkWithBasicHTTP(Uri fileUri)
        {
            HttpClient TestHttpClient = new HttpClient(new HttpClientHandler { UseProxy = false });
            HttpRequestMessage TestRequest = new HttpRequestMessage(HttpMethod.Get, fileUri);
            TestRequest.Version = new Version("1.1");
            HttpResponseMessage TestResponse = null;
            try
            {
                TestResponse = await TestHttpClient.SendAsync(TestRequest);
                TestResponse.EnsureSuccessStatusCode();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.WriteLine(await TestResponse.Content.ReadAsStringAsync());

        }
        async static void Client()
        {
            await SendMessage();
            Console.WriteLine("Gotcha!");
        }
        static Task SendMessage()
        {
            return Task.Run(() =>
            {
                Socket ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                ClientSocket.Connect("127.0.0.1", 904);
                Console.WriteLine("Write your message");
                string Message = Console.ReadLine();
                byte[] MessageInByte = Encoding.ASCII.GetBytes(Message);
                ClientSocket.Send(MessageInByte);
            });
        }
        async static void Server()
        {
            await StartServer();
        }
        static Task StartServer()
        {
            return Task.Run(() =>
            {
                Socket ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                Socket ClientSocket;
                ServerSocket.Bind(new IPEndPoint(IPAddress.Any, 904));
                ServerSocket.Listen(5);
                ClientSocket = ServerSocket.Accept();
                Console.WriteLine("Connection Accept");
                byte[] MessageInBytes = new byte[1024];
                ClientSocket.Receive(MessageInBytes);
                
                string Message = Encoding.ASCII.GetString(MessageInBytes);
                Message.ToUpper();
                Console.WriteLine($"Message has been got: {Message}");
                Console.ReadLine();
            });
        }
        static void Main(string[] args)
        {
            #region TestUris
            // List<Uri> TestUriList = new List<Uri>();
            // TestUriList.Add(new Uri(@"F:\FrontEnd\FirstPage.html"));//[0]
            // TestUriList.Add(new Uri(@"https://ru.wikipedia.org/wiki/URI"));//[1]
            // TestUriList.Add(new Uri(@"https://habr.com/post/215117/"));//[2]
            // TestUriList.Add(new Uri(@"https://alizar.habrahabr.ru"));
            //// WorkWithBasicHTTP(TestUriList[3]); 
            #endregion
            Server();
            Client();
            Thread.Sleep(100000);
            Console.ReadLine();
        }
    }
}
