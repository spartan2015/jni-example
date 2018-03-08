//
// Created by eXpert on 3/7/2018.
//


#ifndef C_EXAMPLE_PLUGINLOADER_H
#define C_EXAMPLE_PLUGINLOADER_H

#include <string>
#include "Plugin.h"


class PluginLoader
{
    static PluginLoader *instance;
public :
    static PluginLoader *getInstance(){
        if (!instance)
        {
            instance = new PluginLoader();
        }
        return instance;
    }
    Plugin *loadPlugin(std::string key, float inputSampleRate, int adapterFlags =0)
    {
        return new Plugin();
    }

};

#endif //C_EXAMPLE_PLUGINLOADER_H
