public class MainClass {

    static {
        System.loadLibrary("libgo");
    }

    // Declare native methods
    public native void helloWorld();
    public native int registerCallback(Callback callback);
    public native void callRegisteredCallback(int id);

    // Define the callback interface
    public interface Callback {
        void callbackMethod();
    }

    // Implement a method to test the callback registration
    public void testCallback() {
        registerCallback(new Callback() {
            @Override
            public void callbackMethod() {
                System.out.println("Callback invoked from Java");
            }
        });
    }

    public static void main(String[] args) {
        MainClass mainClass = new MainClass();
        mainClass.helloWorld();

        // Register and call the callback
        int callbackId = mainClass.registerCallback(new Callback() {
            @Override
            public void callbackMethod() {
                System.out.println("Callback invoked from Java");
            }
        });

        System.out.println("Registered callback with ID: " + callbackId);
        mainClass.callRegisteredCallback(callbackId);
    }
}
