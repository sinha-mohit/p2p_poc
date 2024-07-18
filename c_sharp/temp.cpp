#include <iostream>

// Function to add two numbers and return the result
extern "C" __declspec(dllexport) int AddTwoNumbers(int num1, int num2)
{
    return num1 + num2;
}
