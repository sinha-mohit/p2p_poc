package main

/*
#cgo windows LDFLAGS: -L"C:\Users\mohit\OneDrive\Documents\p2p_poc\go\Cpp_dll" AddLibrary.dll
#include <stdlib.h>

// Declaration of the C# function
extern int AddTwoNumbers(int num1, int num2);
*/
import "C"
import "fmt"

func main() {
    num1 := C.int(5)
    num2 := C.int(10)

    // Call the C# function directly
    sum := C.AddTwoNumbers(num1, num2)
    fmt.Printf("The sum is %d\n", sum)
}
