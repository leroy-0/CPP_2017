//
// Created by Sebastien on 12/01/2018.
//

#include <iostream>
#include <algorithm>
#include "Other/Parse.hpp"

bool
Parse::findInVector(std::vector<Component::Position::Geolocalisation> pos, Component::Position::Geolocalisation what) {
    return (std::find(pos.begin(), pos.end(), what) != pos.end());
}

template<typename Out>
void Parse::split(const std::string &s, char delim, Out result){
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> Parse::split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        Parse::split(s, delim, std::back_inserter(elems));
        return elems;
}

int Parse::checkRFCNumber(std::string toCheck) {
    std::vector<std::string>    tokens = Parse::split(toCheck, ' ');
    int                         nb = std::atoi((*tokens.begin()).c_str());

    return nb;
}
