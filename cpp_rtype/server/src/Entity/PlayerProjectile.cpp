//
// Created by longle-h on 17/01/18.
//

#include "Entity/PlayerProjectile.hpp"

PlayerProjectile::PlayerProjectile(Epibros::Direction projectileDir, int size_x, int size_y) {
    this->physics.Player = true;
    //TODO AJUSTER LA TAILLE
    this->collider.size_y = size_y;
    this->collider.size_x = size_x;
    this->physics.direction = projectileDir;
    this->physics.serverSide = true;
}
