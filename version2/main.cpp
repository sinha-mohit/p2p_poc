#include <iostream>
#include <map>
#include <mutex>

// Define the callback delegate type
typedef void (*CallbackDelegate)();

// A map to store registered callbacks and a mutex to manage concurrent access
std::map<int, CallbackDelegate> callbackRegistry;
std::mutex callbackMutex;
int nextID = 0;

// Exported function to register a callback
extern "C" __declspec(dllexport) int RegisterCallback(CallbackDelegate cb) {
    std::lock_guard<std::mutex> lock(callbackMutex);
    int id = nextID++;
    callbackRegistry[id] = cb;
    return id;
}

// Exported function to call a registered callback
extern "C" __declspec(dllexport) void CallRegisteredCallback(int id) {
    std::lock_guard<std::mutex> lock(callbackMutex);
    auto it = callbackRegistry.find(id);
    if (it != callbackRegistry.end() && it->second != nullptr) {
        std::cout << "Next is calling registered callback from C++" << std::endl;
        it->second();
    } else {
        std::cout << "Callback ID not found or null" << std::endl;
    }
}

// Exported function to print "Hello World" from C++
extern "C" __declspec(dllexport) void HelloWorld() {
    std::cout << "Hello world from C++" << std::endl;
}

int main() {
    // This function is required to create the shared library, but will not be used
    return 0;
}


/*
g++ -shared -o libcpp.dll -Wl,--out-implib,libmain.a -std=c++11 -fPIC main.cpp
*/