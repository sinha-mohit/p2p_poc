using System;
using System.Runtime.InteropServices;

namespace AddLibrary
{
    public class Adder
    {
        // Method to add two numbers and return the result
        [DllImport("AddLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddTwoNumbers(int num1, int num2);
    }
}
