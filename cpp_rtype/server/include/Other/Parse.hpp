//
// Created by Sebastien on 12/01/2018.
//

#ifndef R_TYPE_PARSE_HPP
#define R_TYPE_PARSE_HPP


#include <string>
#include <vector>
#include <sstream>
#include "Component/Position.hpp"

class Parse {
public:
    Parse() = default;
    ~Parse() = default;

    template<typename Out>
    static void split(const std::string &s, char delim, Out result);
    static std::vector<std::string> split(const std::string &s, char delim);

    static bool findInVector(std::vector<Component::Position::Geolocalisation> pos, Component::Position::Geolocalisation what);

    static int checkRFCNumber(std::string toCheck);
};


#endif //R_TYPE_PARSE_HPP
