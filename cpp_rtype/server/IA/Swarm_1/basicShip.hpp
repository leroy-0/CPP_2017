//
// Created by Sebastien on 16/01/2018.
//

#ifndef R_TYPE_BASICSHIP_HPP
#define R_TYPE_BASICSHIP_HPP

#include "Entity/IEnemy.hpp"
#include "../IAi.hpp"



class basicShip : public IAi {
public:
    basicShip(Epibros::SwarmPattern *);
    virtual ~basicShip();

    Epibros::SwarmPattern *getSwarmPattern();
    void        setWaitTime(int);

    Epibros::SwarmPattern   *pattern;


protected:
    int         waitTime;
};


#endif //R_TYPE_BASICSHIP_HPP
