// main.go
package main

/*
#include <stdlib.h>
#include <stdio.h>

typedef void (*CallbackDelegate)();

static void CallCallback(CallbackDelegate cb) {
    cb();
}
*/
import "C"
import (
    "fmt"
    "sync"
)

// A map to store registered callbacks and a mutex to manage concurrent access
var callbackRegistry = make(map[int]C.CallbackDelegate)
var callbackMutex sync.Mutex
var nextID int

//export RegisterCallback
func RegisterCallback(cb C.CallbackDelegate) int {
    callbackMutex.Lock()
    defer callbackMutex.Unlock()
    id := nextID
    nextID++
    callbackRegistry[id] = cb
    return id
}

//export CallRegisteredCallback
func CallRegisteredCallback(id int) {
    callbackMutex.Lock()
    cb, exists := callbackRegistry[id]
    callbackMutex.Unlock()
    if exists && cb != nil {
        fmt.Println("Next is Calling registered callback from Go")
        C.CallCallback(cb)
    } else {
        fmt.Println("Callback ID not found or null")
    }
}

//export HelloWorld
func HelloWorld() {
    fmt.Println("Hello world from Go")
}

func main() {}
