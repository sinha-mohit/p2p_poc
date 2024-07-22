class Main {
    // Load the native library
    static {
        System.loadLibrary("libcppjava");
    }

    // Declare the native methods
    public native void helloWorld();
    public native int registerCallback(Callback callback);
    public native void callRegisteredCallback(int id);

    // Define a Java interface for the callback
    public interface Callback {
        void invoke();
    }

    public static void main(String[] args) {
        Main main = new Main();

        // Define a callback function in Java
        Callback callback = new Callback() {
            @Override
            public void invoke() {
                System.out.println("Callback invoked from Java");
            }
        };

        // Register the callback function via JNI
        int callbackId = main.registerCallback(callback);
        System.out.println("Registered callback with ID: " + callbackId);

        // Call the C++ function that uses the registered callback
        main.helloWorld();

        // Simulate a callback from C++ layer
        main.callRegisteredCallback(callbackId);
    }
}
