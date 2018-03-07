package com.spartan2015;

public class ExampleJni {
    static {
        //System.load("C:\\dev\\c-example\\cmake-build-default\\libc_example.dll");
        System.loadLibrary("c_example");
    }

    public static native char hello();

    public static void main(String[] args) {
        System.out.println("" + hello());
    }
}
