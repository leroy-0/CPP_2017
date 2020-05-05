//
// Created by Sebastien on 15/01/2018.
//

#include "Manager/ServerSideManager.hpp"

void ServerSideManager::manageServerSideEntities(std::vector<Entity> &e, MovementSystem s) {
    for (auto &it : e) {
        if (it.getPhysics().serverSide)
        {
            s.moveEntity(it.getPhysics().direction, it);
        }
    }
}

void ServerSideManager::manageServerSideEntities(std::vector<IProjectile> &e, MovementSystem s) {
    for (auto &it : e) {
        if (it.getPhysics().serverSide)
        {
            if (!s.moveEntity(it.getPhysics().direction, it))
                it.setDead(true);
        }
    }
}
