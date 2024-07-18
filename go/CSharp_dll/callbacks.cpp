// callbacks.cpp
#include <iostream>
#include <functional>
#include <map>

// Define a type for the callback function
typedef void (*CallbackDelegate)();

std::map<int, CallbackDelegate> callbackRegistry;

// Function to register a callback
extern "C" __declspec(dllexport) int __stdcall RegisterCallback(CallbackDelegate cb) {
    static int id = 0;
    callbackRegistry[id] = cb;
    return id++;
}

// Function to call a registered callback
extern "C" __declspec(dllexport) void __stdcall CallRegisteredCallback(int id) {
    auto it = callbackRegistry.find(id);
    if (it != callbackRegistry.end() && it->second != nullptr) {
        std::cout << "Next is Calling registered callback from C++" << std::endl;
        it->second(); // Invoke the callback function
    } else {
        std::cout << "Callback ID not found or null" << std::endl;
    }
}

// A simple function to demonstrate calling from C#
extern "C" __declspec(dllexport) void __stdcall HelloWorld() {
    std::cout << "Hello world from C++" << std::endl;
}
