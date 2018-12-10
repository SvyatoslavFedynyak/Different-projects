using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Net.Sockets;
using System.Text.RegularExpressions;

namespace HTTP_Server
{
    class Server
    {
        #region Fields

        private Socket ServerSocket;
        private int NumOfPossibleConnections=10;

        #endregion

        public Server(int ServerPort)
        {
            ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ServerSocket.Bind(new IPEndPoint(IPAddress.Any, 80));
            
        }
        public void Start()
        {
            ServerSocket.Listen(NumOfPossibleConnections);
            Console.WriteLine($"Server started on port 80\nListening...");
            while (true)
            {
                HandleNewRequest(ServerSocket.Accept());
                Console.WriteLine("Connect Accepted");
            }
            
        }
        private async void HandleNewRequest(Socket ClientSocket)
        {
            await Task.Run(() =>
                {
                    new ClientHandler(ClientSocket);
                });
        }
        ~Server()
        {
            ServerSocket.Disconnect(false);
        }
    }
    class ClientHandler
    {
        public ClientHandler(Socket client)
        {
            string Request = "";
            string Response = "";
            byte[] RequestBuffer = new byte[1024];
            byte[] ResponseBuffer;
            client.Receive(RequestBuffer);
            Request = Encoding.ASCII.GetString(RequestBuffer);
            Console.WriteLine(Request);
            string HtmlContent = "<html><body><h1>It works!</h1></body></html>";
            Response = "HTTP/1.1 200 OK\nContent-type: text/html\nContent-Length:" + HtmlContent.Length.ToString() + "\n\n" + HtmlContent;
            ResponseBuffer = Encoding.ASCII.GetBytes(Response);
            client.Send(ResponseBuffer);
            //Match RequestMatch = Regex.Match(Request, @"^\w+\s+([^\s\?]+)[^\s]*\s+HTTP/.*|");
            //if (RequestMatch  == Match.Empty)
            //{
            //    c
            //}
            
            //string HtmlContent = "<html><body><h1>It works!</h1></body></html>";
            //string Response = "HTTP/1.1 200 OK\nContent-type: text/html\nContent-Length:" + HtmlContent.Length.ToString() + "\n\n" + HtmlContent;
            //byte[] buffer = Encoding.ASCII.GetBytes(Response);
            //client.GetStream().Write(buffer, 0, buffer.Length);
            //client.Close();
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Server MainServer = new Server(80);
            MainServer.Start();
            Console.ReadLine();
        }
    }
}
