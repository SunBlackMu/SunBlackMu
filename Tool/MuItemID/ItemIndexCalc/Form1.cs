using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!CheckTextBox(textBox1) || !CheckTextBox(textBox2))
            {
                MessageBox.Show("You entered the wrong number!", "ERROR!");
                return;
            }

            if (Int32.Parse(textBox1.Text) < 0 || Int32.Parse(textBox1.Text) > 15)
            {
                MessageBox.Show("You entered the wrong Item Group!", "ERROR!");
                return;
            }

            if (Int32.Parse(textBox2.Text) < 0 || Int32.Parse(textBox2.Text) > 255)
            {
                MessageBox.Show("You entered the wrong Item ID!", "ERROR!");
                return;
            }

            textBox3.Text = (Int32.Parse(textBox1.Text) * 512 + Int32.Parse(textBox2.Text)).ToString();
        }

        public bool CheckTextBox(TextBox textbox)
        {
            int result;
            if (String.IsNullOrEmpty(textbox.Text) || !Int32.TryParse(textbox.Text, out result))
            {
                return false;
            }
            return true;
        }
    }
}
