package com.spartan2015;

public class Main {
    public static void main(String[] args) {
        System.out.println("" + ExampleJni.hello());

        Plugin plugin = PluginLoader.getInstance().loadPlugin("some",1.0f);
        System.out.println("Name: " + plugin.getName());
        System.out.println("Description: " + plugin.getDescription());
        System.out.println("Identifier: " + plugin.getIdentifier());
        System.out.println("Version: " + plugin.getPluginVersion());
        plugin.destroy();
        PluginLoader.getInstance().destroy();
    }
}
