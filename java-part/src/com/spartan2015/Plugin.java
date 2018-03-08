package com.spartan2015;

public class Plugin extends BaseJniClass{

    public Plugin(long handle){
        this.nativeHandle = handle;
    }
    public native String getIdentifier();
    public native String getName();
    public native String getDescription();
    public native int getPluginVersion();
}
