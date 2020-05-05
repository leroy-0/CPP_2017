//
// Created by Sebastien on 16/01/2018.
//

#ifndef R_TYPE_AENEMY_HPP
#define R_TYPE_AENEMY_HPP


#include "ICharacter.hpp"
#include "EnemyProjectile.hpp"
#include "../../IA/IAi.hpp"

class IEnemy : public ICharacter {
public:
    IEnemy();
    virtual ~IEnemy() = default;

    virtual IProjectile &getProjectile();
    IAi     *ai;

private:
    IProjectile     projectile;
};


#endif //R_TYPE_AENEMY_HPP
