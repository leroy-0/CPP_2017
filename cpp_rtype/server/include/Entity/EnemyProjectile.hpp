//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_ENEMYPROJECTILE_HPP
#define R_TYPE_ENEMYPROJECTILE_HPP


#include "IProjectile.hpp"

class EnemyProjectile : public IProjectile {
public:
    EnemyProjectile(Epibros::Direction projectileDir = Epibros::BACKWARD, int size_x = 2, int size_y = 1);
    virtual ~EnemyProjectile() = default;
};


#endif //R_TYPE_ENEMYPROJECTILE_HPP
