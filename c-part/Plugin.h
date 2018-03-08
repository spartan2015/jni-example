//
// Created by eXpert on 3/7/2018.
//

#ifndef C_EXAMPLE_PLUGIN_H
#define C_EXAMPLE_PLUGIN_H

#include <string>

class Plugin{
    static int count;
public:
    Plugin();
    std::string getIdentifier();
    std::string getName() ;
    std::string getDescription() ;
    int getPluginVersion() ;
};

#endif //C_EXAMPLE_PLUGIN_H
