//
// Created by Sébastien on 20/01/2018.
//

#include <iostream>
#include <dlfcn.h>
#include "Other/Linux.hpp"

IAi *Linux::loadSharedLibrary(const std::string &lib) {
    IAi    *(*ptr)();

    std::string finalLib = std::string("ia/libia_" + lib + ".so");
    void *handler = dlopen(finalLib.c_str(), RTLD_LAZY | RTLD_NOW);
    if (!handler) {
        finalLib = std::string("../" + finalLib);
        handler = dlopen(finalLib.c_str(), RTLD_LAZY | RTLD_NOW);
        if (!handler)
            throw "Failed to load library: " + finalLib;
        else {
            ptr = reinterpret_cast<IAi  *(*)()>(dlsym(handler, "getIA"));
            return (ptr());
        }
    }
    else {
        ptr = reinterpret_cast<IAi  *(*)()>(dlsym(handler, "getIA"));
        return (ptr());
    }
}