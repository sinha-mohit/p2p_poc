using System;
using System.Runtime.InteropServices;



public class MainClass
{
    // Define the callback delegate
    public delegate void CallbackDelegate();

    // Import the C++ functions
    [DllImport("libgo.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern void HelloWorld();

    [DllImport("libgo.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int RegisterCallback(CallbackDelegate callback);

    [DllImport("libgo.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern void CallRegisteredCallback(int id);

    static void Main()
    {
        // Define a callback function in C#
        CallbackDelegate callback = () =>
        {
            Console.WriteLine("Callback invoked from C#");
        };

        // Register the callback function via C++ layer
        int callbackId = RegisterCallback(callback);
        Console.WriteLine($"Registered callback with ID: {callbackId}");

        // Call the C++ function that uses the registered callback
        HelloWorld();

        // Simulate a callback from C++ layer
        CallRegisteredCallback(callbackId);
    }
}
