//
// Created by Yan on 10/3/2017.
//

#ifndef PROJECT_TOOLS_HPP
#define PROJECT_TOOLS_HPP

#include <string>
#include "termcolor.hpp"

class Tools {
public:
    static void checkDir(std::string key);
    static void printServerLogGreen(const std::string & log, const std::string & ip);
    static void printServerLogRed(const std::string & log, const std::string & ip);
};

#endif //PROJECT_TOOLS_HPP
