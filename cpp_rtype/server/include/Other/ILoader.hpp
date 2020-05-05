//
// Created by Sébastien on 20/01/2018.
//

#ifndef R_TYPE_ILOADER_HPP
#define R_TYPE_ILOADER_HPP

#include "../../IA/IAi.hpp"

class ILoader {
public:
    ILoader() = default;
    virtual ~ILoader() = default;

   virtual IAi *loadSharedLibrary(const std::string &) = 0;

};

#endif //R_TYPE_ILOADER_HPP
