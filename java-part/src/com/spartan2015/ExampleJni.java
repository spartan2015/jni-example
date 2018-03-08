package com.spartan2015;

public class ExampleJni {
    static {
        System.load("C:\\dev\\git\\jni-example\\c-part\\cmake-build-default\\libc_example.dll");
        //System.loadLibrary("c_example");
    }

    public static native char hello();

    public static void main(String[] args) {
        System.out.println("" + ExampleJni.hello());
    }
}
