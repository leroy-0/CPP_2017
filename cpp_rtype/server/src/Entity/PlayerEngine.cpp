//
// Created by longle-h on 17/01/18.
//

#include "Entity/PlayerProjectile.hpp"
#include "Entity/PlayerEngine.hpp"



IProjectile         &PlayerEngine::getProjectile()
{
    return this->projectile;
}

PlayerEngine::PlayerEngine() : ICharacter(), projectile(PlayerProjectile()) {
    this->getPhysics().Player = true;
}
