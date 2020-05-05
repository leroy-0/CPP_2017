//
// Created by Sebastien on 16/01/2018.
//

#include "Entity/IEnemy.hpp"

IEnemy::IEnemy() : ICharacter(), projectile(EnemyProjectile()) {
    this->getPhysics().Enemy = true;
}

IProjectile &IEnemy::getProjectile() {
    return this->projectile;
}
