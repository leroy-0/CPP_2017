//
// Created by Sebastien on 15/01/2018.
//

#include <iostream>
#include "System/MovementSystem.hpp"
#include "Rules.hpp"

bool MovementSystem::moveEntity(Epibros::Direction direction, Entity &e) const {
    int new_x, new_y;
    //TODO Variation a gérer
    int variation = 1;

    new_x = e.getPosition().x;
    new_y = e.getPosition().y;

    if (!e.isDead()) {
        switch (direction) {
            case Epibros::FORWARD:
                new_x += variation * e.getSpeed();
                break;
            case Epibros::BACKWARD:
                new_x -= variation * e.getSpeed();
                break;
            case Epibros::UP:
                new_y -= variation * e.getSpeed();
                break;
            case Epibros::DOWN:
                new_y += variation * e.getSpeed();
                break;
            case Epibros::BACKWARD_UP:
                new_x -= variation * e.getSpeed();
                new_y -= variation * e.getSpeed();
            case Epibros::BACKWARD_DOWN:
                new_x -= variation * e.getSpeed();
                new_y += variation * e.getSpeed();
            case Epibros::FORWARD_UP:
                new_x += variation * e.getSpeed();
                new_y -= variation * e.getSpeed();
            case Epibros::FORWARD_DOWN:
                new_x += variation * e.getSpeed();
                new_y += variation * e.getSpeed();
            default:
                break;
        }
        if (new_x < 0 || new_y < 0 || new_x > MAX_WIDTH || new_y > MAX_HEIGHT)
            return false;

        e.setPosition(new_x, new_y);
        e.updatePositionInMap();

        return true;
    }
    return false;
}

bool MovementSystem::moveEntity(Epibros::Direction direction, IEnemy *e) const {
    int new_x, new_y;
    //TODO Variation a gérer
    int variation = 1;

    new_x = e->getPosition().x;
    new_y = e->getPosition().y;

    if (!e->isDead()) {
        switch (direction) {
            case Epibros::FORWARD:
                new_x += variation * e->getSpeed();
                break;
            case Epibros::BACKWARD:
                new_x -= variation * e->getSpeed();
                break;
            case Epibros::UP:
                new_y -= variation * e->getSpeed();
                break;
            case Epibros::DOWN:
                new_y += variation * e->getSpeed();
                break;
            case Epibros::BACKWARD_UP:
                new_x -= variation * e->getSpeed();
                new_y -= variation * e->getSpeed();
            case Epibros::BACKWARD_DOWN:
                new_x -= variation * e->getSpeed();
                new_y += variation * e->getSpeed();
            case Epibros::FORWARD_UP:
                new_x += variation * e->getSpeed();
                new_y -= variation * e->getSpeed();
            case Epibros::FORWARD_DOWN:
                new_x += variation * e->getSpeed();
                new_y += variation * e->getSpeed();
            default:
                break;
        }
        if (new_x < 0 || new_y < 0 || new_x > MAX_WIDTH || new_y > MAX_HEIGHT)
            return false;

        e->setPosition(new_x, new_y);
        e->updatePositionInMap();

        return true;
    }
    return false;
}
