//
// Created by Sebastien on 15/01/2018.
//

#ifndef R_TYPE_SERVERSIDEMANAGER_HPP
#define R_TYPE_SERVERSIDEMANAGER_HPP

#include "Entity/IProjectile.hpp"
#include "Entity/Entity.hpp"
#include "MovementSystem.hpp"


class ServerSideManager {
public:
    ServerSideManager() = default;
    virtual ~ServerSideManager() = default;

    void        manageServerSideEntities(std::vector<Entity> &e, MovementSystem s);
    void        manageServerSideEntities(std::vector<IProjectile> &e, MovementSystem s);
};


#endif //R_TYPE_SERVERSIDEMANAGER_HPP
