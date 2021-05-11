using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace FrontEnd_Calc
{
    static class Program
    {
        public const string StringCalcDLL = @"\..\..\..\..\..\x64\Debug\Backend_Calc.dll";  //4 lvls up and x64\dbg\.dll    //! FOR PUBLISH CHANGE TO  @"Backend_Calc.dll" and paste dll where exe is
                                                                                            // public const string StringCalcDLL = @"D:\BckToSchool\MyProjects\StringCalc\x64\Debug\Backend_Calc.dll";
        [DllImport(StringCalcDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void intro();

    static void Main()
        { 

            intro(); 
            
            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            
        }
    }
}
