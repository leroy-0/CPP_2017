//
// Created by Sebastien on 15/01/2018.
//

#include "Clock.hpp"
#include <sstream>

Clock::Clock() : start(time(nullptr)) {
}

int Clock::getElapsedTime(){
    int duration;
    duration = static_cast<int>(time(nullptr) - this->start);
    return duration;
}

std::string Clock::getElapsedTimeString() {
    std::ostringstream strs;
    strs << this->getElapsedTime();
    return strs.str();

}
