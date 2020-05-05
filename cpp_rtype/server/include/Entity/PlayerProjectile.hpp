//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_PLAYERPROJECTILE_HPP
#define R_TYPE_PLAYERPROJECTILE_HPP


#include "Entity/IProjectile.hpp"

class PlayerProjectile : public IProjectile {
public:
    PlayerProjectile(Epibros::Direction projectileDir = Epibros::FORWARD, int size_x = 2, int size_y = 1);
    virtual ~PlayerProjectile() = default;
};


#endif //R_TYPE_PLAYERPROJECTILE_HPP
