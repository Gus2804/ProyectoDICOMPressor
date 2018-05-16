using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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
            BtnConv.Enabled = true;
        }

        private void BtnConv_Click(object sender, EventArgs e)
        {   
            BtnCompr.Enabled = true;
        }

        private void BtnCompr_Click(object sender, EventArgs e)
        {
            BtnEnviar.Enabled = true;
        }

        private void BtnEnviar_Click(object sender, EventArgs e)
        {
            Form envio= new Envio.EnvioForm();
            envio.Show();


        }

        private void Principal_Load(object sender, EventArgs e)
        {

        }
    }
}
