using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Collections;

namespace Recepcion
{
    public partial class Form1 : Form
    {
        private ArrayList nSockets;
        int imagen;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            IPHostEntry IPHost = Dns.GetHostByName(Dns.GetHostName());
            lblStatus.Text = "My IP address is " + IPHost.AddressList[0].ToString();
            nSockets = new ArrayList();
            Thread thdListener = new Thread(new ThreadStart(listenerThread));
            thdListener.Start();

        }
        public void listenerThread()
        {
            TcpListener tcpListener = new TcpListener(8080);
            tcpListener.Start();
            while (true)
            {
                Socket handlerSocket = tcpListener.AcceptSocket();
                if (handlerSocket.Connected)
                {
                    Control.CheckForIllegalCrossThreadCalls = false;
                    lbConnections.Items.Add(
                    handlerSocket.RemoteEndPoint.ToString() + " connected.");
                    lock (this)
                    {
                        nSockets.Add(handlerSocket);
                    }
                    ThreadStart thdstHandler = new
                    ThreadStart(handlerThread);
                    Thread thdHandler = new Thread(thdstHandler);
                    thdHandler.Start();
                }
            }
        }
        public void handlerThread()
        {
            Socket handlerSocket = (Socket)nSockets[nSockets.Count - 1];
            NetworkStream networkStream = new NetworkStream(handlerSocket);
            int thisRead = 0;
            int blockSize = 1024;
            
            Byte[] dataByte = new Byte[blockSize];
            lock (this)
            
            {
                Stream fileStream = File.OpenWrite("C:\\Users\\T_idelarosa\\Dropbox\\TT\\Transmision\\Recepcion\\recibidas\\" + imagen+".jpg");
                while (true)
                {
                    thisRead = networkStream.Read(dataByte, 0, blockSize);
                    fileStream.Write(dataByte, 0, thisRead);
                    if (thisRead == 0) break;
                }
                fileStream.Close();
            }
            lbConnections.Items.Add("File Written");
            imagen++;
            handlerSocket = null;
        }


    }
}
