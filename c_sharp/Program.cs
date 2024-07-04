using System;

class AddNumbers
{
    static int AddTwoNumbers(int num1, int num2)
    {
        return num1 + num2;
    }

    static void Main()
    {
        int number1 = 5;
        int number2 = 10;
        int result = AddTwoNumbers(number1, number2);
        
        Console.WriteLine("The sum of {0} and {1} is {2}", number1, number2, result);
    }
}
