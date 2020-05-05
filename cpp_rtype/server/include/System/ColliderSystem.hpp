//
// Created by Sebastien on 15/01/2018.
//

#ifndef R_TYPE_COLLIDERMANAGER_HPP
#define R_TYPE_COLLIDERMANAGER_HPP

#include <Entity/PlayerEngine.hpp>
#include "Entity/IProjectile.hpp"
#include "Entity/IEnemy.hpp"
#include "System/ASystem.hpp"
#include "Entity/Entity.hpp"

class ColliderSystem : public ASystem {
public:
    ColliderSystem() = default;
    virtual ~ColliderSystem() = default;

    void checkCollision(std::vector<Entity> &, Entity&);
    void checkCollision(std::vector<IEnemy *> &, Entity&);
    void checkCollision(std::vector<IProjectile> &, Entity&);
    void checkCollision(std::vector<PlayerEngine> &, Entity*);

private:
    void checkDead(std::vector<Entity> &, Entity&);
    void checkDead(std::vector<Entity*> &, Entity&);
    void checkDead(std::vector<Entity> &, Entity*);
};


#endif //R_TYPE_COLLIDERMANAGER_HPP
