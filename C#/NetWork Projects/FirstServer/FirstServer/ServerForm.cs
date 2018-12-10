using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace FirstServer
{
    public partial class ServerForm : Form
    {
        bool ServerWork = false;
        int ServerPort = 0;
        public ServerForm()
        {
            InitializeComponent();
        }

        async private void StartServerButton_Click(object sender, EventArgs e)
        {
            await StartServer();
        }
        Task StartServer()
        {
            return Task.Run(() =>
                {
                    ServerWork = true;
                    Socket ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    Socket ClientSocket;
                    ServerSocket.Bind(new IPEndPoint(IPAddress.Any, Convert.ToInt32(PortTexBox.Text)));
                    Invoke((Action)delegate
                    {
                        ServerTextBox.AppendText($"Server Started\n");
                    });
                    ServerSocket.Listen(10);
                    do
                    {
                        ClientSocket = ServerSocket.Accept();
                        ProcessRequest(ClientSocket);
                    } while (ServerWork == true);
                    ServerSocket.Close();
                });
        }
        async private void ProcessRequest(Socket TargetSocet)
        {
            await GenerateAnswer(TargetSocet);
        }
        Task GenerateAnswer(Socket TargetSocet)
        {
            return Task.Run(() =>
            {
                byte[] MessageInBytes = new byte[1024];
                string Message;
                Invoke((Action)delegate
                {
                    ServerTextBox.AppendText("Connection Accept\n");
                });
                TargetSocet.Receive(MessageInBytes);
                Message = Encoding.ASCII.GetString(MessageInBytes);
                Invoke((Action)delegate
                {
                    ServerTextBox.AppendText($"Message got: {Message}");
                    ServerTextBox.AppendText("\n");
                });
                Message = Message.ToUpper();
                Thread.Sleep(5000);
                MessageInBytes = Encoding.ASCII.GetBytes(Message);
                TargetSocet.Send(MessageInBytes);
                Invoke((Action)delegate
                {
                    ServerTextBox.AppendText($"Answer sent: {Message}");
                    ServerTextBox.AppendText("\n");
                });
                TargetSocet.Close();
            });
        }
        private void ServerForm_Load(object sender, EventArgs e)
        {

        }

        private void StopServerButton_Click(object sender, EventArgs e)
        {
            ServerWork = false;
            ServerTextBox.AppendText("Server Stopped\n");
        }
    }
}
