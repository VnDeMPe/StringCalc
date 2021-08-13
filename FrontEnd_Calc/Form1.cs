using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace FrontEnd_Calc
{
    public partial class Form1 : Form
    {

        public const string StringCalcDLL = @"\..\..\..\..\..\x64\Debug\Backend_Calc.dll";

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void AdddAnsi([MarshalAs(UnmanagedType.LPStr)] string str); // delegat 


        [DllImport(StringCalcDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern double MarshalStringCalc(string inputString, AdddAnsi str, int numFinDecimal);


        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listOutputConsole.Clear();

            var logList = new List<string>();
            double result = MarshalStringCalc(stringInputBox.Text, logList.Add, (int)numFinDigits.Value);
            
            stringOutputBox.Text = Convert.ToString(result);

            listPastResults.Items.Insert(0, logList[0] + " = " + result);
            logList[0] = ("Output String to calculate = " + logList[0]);

            foreach (string str in logList)
            {
                listOutputConsole.AppendText(str+"\r\n");
            }

        }

    }
}
