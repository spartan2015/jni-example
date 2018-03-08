//
// Created by eXpert on 3/8/2018.
//
#include "Plugin.h"
int Plugin::count;

Plugin::Plugin() {
    ++count;
}

std::string Plugin::getDescription() {
        return "Description";
}

std::string Plugin::getName() {
    return "Name";
}

std::string Plugin::getIdentifier() {
    return "Identifier";
}

int Plugin::getPluginVersion()  {
    return 99;
}