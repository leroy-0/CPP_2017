//
// Created by Sebastien on 16/01/2018.
//


#include <Rules.hpp>
#include <iostream>
#include "basicShip.hpp"
#include "../../include/Rules.hpp"

basicShip::basicShip(Epibros::SwarmPattern *s) {
    pattern = s;
}

Epibros::SwarmPattern *basicShip::getSwarmPattern() {
    return pattern;
}
void basicShip::setWaitTime(int wait) {
    waitTime = wait;
}

basicShip::~basicShip() = default;

extern "C" IAi*getIA() {
    Epibros::SwarmPattern * swarm = new Epibros::SwarmPattern();
    swarm->patternContainer.push_back(new Epibros::Pattern(0, 0));
    swarm->patternContainer.push_back(new Epibros::Pattern(1, -1));
    swarm->patternContainer.push_back(new Epibros::Pattern(2, -2));
    swarm->patternContainer.push_back(new Epibros::Pattern(2, 2));
    swarm->patternContainer.push_back(new Epibros::Pattern(3, 0));
    swarm->nbShip = 5;
    basicShip *_new = new basicShip(swarm);
    return _new;
}
