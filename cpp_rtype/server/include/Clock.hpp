//
// Created by Sebastien on 15/01/2018.
//

#ifndef R_TYPE_CLOCK_HPP
#define R_TYPE_CLOCK_HPP

#include <ctime>
#include <string>

class Clock {
public:
    Clock();
    virtual ~Clock() = default;

    int          getElapsedTime();
    std::string     getElapsedTimeString();
private:
    std::time_t   start;
};


#endif //R_TYPE_CLOCK_HPP
