//
// Created by Sebastien on 15/01/2018.
//

#ifndef R_TYPE_SYSTEM_HPP
#define R_TYPE_SYSTEM_HPP

#include "System/ColliderSystem.hpp"
#include "System/IASystem.hpp"
#include "System/MovementSystem.hpp"
#include "ServerSideManager.hpp"

class Manager {
public:
    Manager();
    virtual ~Manager() = default;

    ColliderSystem      getColliderSytem() const;
    MovementSystem      getMovementSystem() const;
    IASystem            getIaSystem() const;
    ServerSideManager   getServerSideManager() const;

private:
    ColliderSystem      collider;
    MovementSystem      movement;
    IASystem            ia;
    ServerSideManager   ssmanager;
};

#endif //R_TYPE_SYSTEM_HPP
