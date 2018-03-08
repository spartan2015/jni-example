package com.spartan2015;

public class PluginLoader extends BaseJniClass {
    static PluginLoader singleton;

    private PluginLoader() {
    }

    public static synchronized PluginLoader getInstance() {
        if (singleton == null) {
            singleton = new PluginLoader();
            singleton.init();
        }
        return singleton;
    }

    private native void init();

    public Plugin loadPlugin(String key, float inputSampleRate) {
        return new Plugin(loadPluginNative(key, inputSampleRate));
    }

    private native long loadPluginNative(String key, float inputSampleRate);

}
