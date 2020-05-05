//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP

#include "Entity/PlayerProjectile.hpp"
#include "Entity/ICharacter.hpp"

class PlayerEngine : public ICharacter {
public:
    PlayerEngine();
    virtual ~PlayerEngine() = default;

    IProjectile       &getProjectile();

private:
    IProjectile       projectile;
};


#endif //R_TYPE_PLAYER_HPP
