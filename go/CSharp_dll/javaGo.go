package main

/*
#include <stdlib.h>
#include <stdio.h>
#include "MainClass.h"

typedef void (*CallbackDelegate)();

static void CallCallback(CallbackDelegate cb) {
    cb();
}
*/
import "C"
import (
    "fmt"
    "sync"
    "unsafe"
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
        fmt.Println("Calling registered callback from Go")
        C.CallCallback(cb)
    } else {
        fmt.Println("Callback ID not found or null")
    }
}

//export HelloWorld
func HelloWorld() {
    fmt.Println("Hello world from Go")
}

// JNI function to register callback
//export Java_MainClass_registerCallback
func Java_MainClass_registerCallback(env *C.JNIEnv, clazz C.jclass, callback C.jobject) C.jint {
    // Store the callback
    callbackDelegate := C.CallbackDelegate(callback)
    return C.jint(RegisterCallback(callbackDelegate))
}

// JNI function to call registered callback
//export Java_MainClass_callRegisteredCallback
func Java_MainClass_callRegisteredCallback(env *C.JNIEnv, clazz C.jclass, id C.jint) {
    CallRegisteredCallback(int(id))
}

// JNI function to call helloWorld
//export Java_MainClass_helloWorld
func Java_MainClass_helloWorld(env *C.JNIEnv, clazz C.jclass) {
    HelloWorld()
}

func main() {}
