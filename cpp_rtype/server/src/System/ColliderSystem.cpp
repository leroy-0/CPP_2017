//
// Created by Sebastien on 15/01/2018.
//

#include <iostream>
#include "Other/Parse.hpp"
#include "ColliderSystem.hpp"

void ColliderSystem::checkCollision(std::vector<Entity> &allEntity, Entity &check) {
    std::vector<Entity> toCheck;

    for (auto pos = check.getPosition().posInMap.begin(); pos != check.getPosition().posInMap.end(); pos++) {
        for (auto &entity : allEntity) {
            if (entity == check)
                continue;
            if (Parse::findInVector(entity.getPosition().posInMap, (*pos)))
                toCheck.push_back(entity);
        }
    }

    checkDead(toCheck, check);
}

void ColliderSystem::checkDead(std::vector<Entity> &toCheck, Entity &check) {
    int x = check.getPosition().x;
    int y = check.getPosition().y;
    int size_x = x + check.getCollider().size_x;
    int size_y = y + check.getCollider().size_y;

    for (auto &it : toCheck) {
        if ((check.getPhysics().Player && it.getPhysics().Enemy) ||
            (check.getPhysics().Enemy && it.getPhysics().Player)
            && !check.isDead() && !it.isDead())
        {
            int entity_x = it.getPosition().x;
            int entity_size_x = entity_x + it.getCollider().size_x;
            int entity_y = it.getPosition().y;
            int entity_size_y = entity_y + it.getCollider().size_y;


            if (
                //x,y
                    ((x >= entity_x && x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y + collider_size_y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y)) ||
                    // x, y + collider_size_y
                    ((x >= entity_x && x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y))
                    )
            {
                check.setDead(true);
                it.setDead(true);
            }
        }

    }
}

void ColliderSystem::checkCollision(std::vector<IProjectile> &allEntity, Entity &check) {
    std::vector<Entity> toCheck;

    for (auto pos = check.getPosition().posInMap.begin(); pos != check.getPosition().posInMap.end(); pos++) {
        for (auto &entity : allEntity) {
            if (entity == check)
                continue;
            if (Parse::findInVector(entity.getPosition().posInMap, (*pos))) {
                toCheck.push_back(entity);
            }
        }
    }

    checkDead(toCheck, check);
}

void ColliderSystem::checkCollision(std::vector<IEnemy *> &allEntity, Entity &check) {
    std::vector<Entity*> toCheck;

    for (auto pos = check.getPosition().posInMap.begin(); pos != check.getPosition().posInMap.end(); pos++) {
        for (auto &entity : allEntity) {
            if (*entity == check)
                continue;
            if (Parse::findInVector(entity->getPosition().posInMap, (*pos)))
                toCheck.push_back(entity);
        }
    }

    checkDead(toCheck, check);
}

void ColliderSystem::checkCollision(std::vector<PlayerEngine> &allEntity, Entity *check) {
    std::vector<Entity> toCheck;

    for (auto pos = check->getPosition().posInMap.begin(); pos != check->getPosition().posInMap.end(); pos++) {
        for (auto &entity : allEntity) {
            if (entity == *check)
                continue;
            if (Parse::findInVector(entity.getPosition().posInMap, (*pos)))
                toCheck.push_back(entity);
        }
    }

    checkDead(toCheck, check);
}

void ColliderSystem::checkDead(std::vector<Entity *> &toCheck, Entity &check) {
    int x = check.getPosition().x;
    int y = check.getPosition().y;
    int size_x = x + check.getCollider().size_x;
    int size_y = y + check.getCollider().size_y;

    for (auto &it : toCheck) {
        if ((check.getPhysics().Player && it->getPhysics().Enemy) ||
            (check.getPhysics().Enemy && it->getPhysics().Player)
            && !check.isDead() && !it->isDead())
        {
            int entity_x = it->getPosition().x;
            int entity_size_x = entity_x + it->getCollider().size_x;
            int entity_y = it->getPosition().y;
            int entity_size_y = entity_y + it->getCollider().size_y;


            if (
                //x,y
                    ((x >= entity_x && x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y + collider_size_y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y)) ||
                    // x, y + collider_size_y
                    ((x >= entity_x && x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y))
                    )
            {
                check.setDead(true);
                it->setDead(true);
            }
        }

    }
}
//void ColliderSystem::checkDead(std::vector<Entity> &toCheck, Entity &check) {

void ColliderSystem::checkDead(std::vector<Entity> &toCheck, Entity *check) {
    int x = check->getPosition().x;
    int y = check->getPosition().y;
    int size_x = x + check->getCollider().size_x;
    int size_y = y + check->getCollider().size_y;

    for (auto &it : toCheck) {
        if ((check->getPhysics().Player && it.getPhysics().Enemy) ||
            (check->getPhysics().Enemy && it.getPhysics().Player)
            && !check->isDead() && !it.isDead())
        {
            int entity_x = it.getPosition().x;
            int entity_size_x = entity_x + it.getCollider().size_x;
            int entity_y = it.getPosition().y;
            int entity_size_y = entity_y + it.getCollider().size_y;


            if (
                //x,y
                    ((x >= entity_x && x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (y >= entity_y && y <= entity_size_y)) ||
                    // x + collider_size_x, y + collider_size_y
                    ((size_x >= entity_x && size_x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y)) ||
                    // x, y + collider_size_y
                    ((x >= entity_x && x <= entity_size_x) && (size_y >= entity_y && size_y <= entity_size_y))
                    )
            {
                check->setDead(true);
                it.setDead(true);
            }
        }

    }
}
