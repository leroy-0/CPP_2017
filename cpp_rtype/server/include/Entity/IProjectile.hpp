//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_IPROJECTILE_HPP
#define R_TYPE_IPROJECTILE_HPP

#include "Entity.hpp"

class IProjectile : public Entity {
public:
    IProjectile();
    virtual ~IProjectile() = default;
};


#endif //R_TYPE_IPROJECTILE_HPP
