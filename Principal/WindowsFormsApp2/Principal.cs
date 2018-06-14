using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Envio;

namespace WindowsFormsApp2
{
   
    public partial class Principal : Form
    {
        public Principal()
        {
            InitializeComponent();
        }

        private void BtnElegir_Click(object sender, EventArgs e)
        {
            openFileDialogImg.ShowDialog();
            Rut.Text = openFileDialogImg.FileName;
            ImagenBox.Load(Rut.Text);
            BtnConv.Enabled = true;
            Process.Start(Rut.Text);


        }

        private void BtnConv_Click(object sender, EventArgs e)
        {   
            BtnCompr.Enabled = true;
            Stream fileStream = File.OpenRead(Rut.Text);
        }

        private void BtnCompr_Click(object sender, EventArgs e)
        {
            BtnEnviar.Enabled = true;
        }

        private void BtnEnviar_Click(object sender, EventArgs e)
        {
            Form envform = new Envio.EnvioForm();
            envform.Show();
        }
    }
}
