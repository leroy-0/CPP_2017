//
// Created by Sebastien on 15/01/2018.
//

#include "Manager/Manager.hpp"

Manager::Manager() {
    this->movement = MovementSystem();
    this->collider = ColliderSystem();
    this->ia = IASystem();

}

ColliderSystem Manager::getColliderSytem() const {
    return this->collider;
}

MovementSystem Manager::getMovementSystem() const {
    return this->movement;
}

IASystem Manager::getIaSystem() const {
    return this->ia;
}

ServerSideManager Manager::getServerSideManager() const {
    return this->ssmanager;
}
