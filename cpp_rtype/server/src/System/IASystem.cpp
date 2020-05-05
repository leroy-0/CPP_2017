//
// Created by Sebastien on 16/01/2018.
//

#include <System/MovementSystem.hpp>
#include <System/ColliderSystem.hpp>
#include "IASystem.hpp"

void
IASystem::manageIA(std::vector<IEnemy *> &allEnnemies, MovementSystem m, std::vector<PlayerEngine> p, std::vector<IProjectile> pr,
                   ColliderSystem cs) {
    for (auto &e : allEnnemies) {
        if (e->getPosition().x > MAX_WIDTH) {
            e->setPosition(e->getPosition().x - 1, e->getPosition().y);
        } else if (e->getPosition().y > MAX_HEIGHT) {
            e->setPosition(e->getPosition().x, e->getPosition().y - 1);
        } else {
            if (!m.moveEntity(Epibros::BACKWARD, *e))
                e->setDead(true);
        }
        cs.checkCollision(p, e);
    }
}
