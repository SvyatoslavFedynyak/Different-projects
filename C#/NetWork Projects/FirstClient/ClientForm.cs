using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;

namespace FirstClient
{
    public partial class ClientForm : Form
    {
        public ClientForm()
        {
            InitializeComponent();
        }
        
        async private void ClientSendButton_Click(object sender, EventArgs e)
        {
            await SendMessage();    
        }
        Task SendMessage()
        {
            return Task.Run(() =>
            {
                Socket ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                ClientSocket.Connect(IPTextBox.Text, Convert.ToInt32(PortTextBox.Text));
                string Message = ClientMessageTextBox.Text;
                byte[] MessageInByte = Encoding.ASCII.GetBytes(Message);
                ClientSocket.Send(MessageInByte);
                Invoke((Action)delegate
                {
                    ConsoleTextBox.AppendText($"Message sent: {ClientMessageTextBox.Text} \n");
                });
                ClientSocket.Receive(MessageInByte);
                Message = Encoding.ASCII.GetString(MessageInByte);
                Invoke((Action)delegate
                {
                    ConsoleTextBox.AppendText($"Server returns: {Message}\n");
                });
                ClientSocket.Close();
            });
        }
    }
}
