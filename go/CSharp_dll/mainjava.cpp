#include <jni.h>
#include <iostream>
#include <map>
#include <mutex>

std::map<int, jobject> callbackRegistry;
std::mutex callbackMutex;
int nextID = 0;
JavaVM* javaVM = nullptr;

// Define the callback delegate type
typedef void (*CallbackDelegate)();

extern "C" {

// Helper function to call the Java callback
void callJavaCallback(JNIEnv* env, jobject callback) {
    jclass callbackClass = env->GetObjectClass(callback);
    jmethodID invokeMethod = env->GetMethodID(callbackClass, "invoke", "()V");
    if (invokeMethod == nullptr) {
        std::cerr << "Callback method not found!" << std::endl;
        return;
    }
    env->CallVoidMethod(callback, invokeMethod);
}

// Register the callback
JNIEXPORT jint JNICALL Java_Main_registerCallback(JNIEnv* env, jobject obj, jobject callback) {
    std::lock_guard<std::mutex> lock(callbackMutex);
    int id = nextID++;
    callbackRegistry[id] = env->NewGlobalRef(callback);
    return id;
}

// Call the registered callback
JNIEXPORT void JNICALL Java_Main_callRegisteredCallback(JNIEnv* env, jobject obj, jint id) {
    std::lock_guard<std::mutex> lock(callbackMutex);
    auto it = callbackRegistry.find(id);
    if (it != callbackRegistry.end() && it->second != nullptr) {
        std::cout << "Next is calling registered callback from C++" << std::endl;
        callJavaCallback(env, it->second);
    } else {
        std::cout << "Callback ID not found or null" << std::endl;
    }
}

// Print "Hello World" from C++
JNIEXPORT void JNICALL Java_Main_helloWorld(JNIEnv* env, jobject obj) {
    std::cout << "Hello world from C++" << std::endl;
}
}

// Entry point to ensure the shared library is created
int main() {
    return 0;
}
