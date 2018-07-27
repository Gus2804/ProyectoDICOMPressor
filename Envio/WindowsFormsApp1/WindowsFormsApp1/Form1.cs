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
using System.Diagnostics;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        TextBox dynamicTextBox = new TextBox();
        OpenFileDialog openFileDialog = new OpenFileDialog();

        public Form1()
        {
            InitializeComponent();
        }

       

        private void btnSend_Click(object sender, EventArgs e)
        {
            Stream fileStream = File.OpenRead(tbFilename.Text);
            // Alocate memory space for the file
            byte[] fileBuffer = new byte[fileStream.Length];
            fileStream.Read(fileBuffer, 0, (int)fileStream.Length);
            // Open a TCP/IP Connection and send the data
            TcpClient clientSocket = new TcpClient(tbServer.Text, 8080);
            NetworkStream networkStream = clientSocket.GetStream();
            networkStream.Write(fileBuffer, 0, fileBuffer.GetLength(0));
            networkStream.Close();

        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
            tbFilename.Text = openFileDialog.FileName;
        }

        private void salirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Process proceso in Process.GetProcesses())
            {
                if (proceso.ProcessName == "Envio")
                {
                    proceso.Kill();
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            foreach (Process proceso in Process.GetProcesses())
            {
                if (proceso.ProcessName == "Envio")
                {
                    proceso.Kill();
                }
            }
        }
    }
}
