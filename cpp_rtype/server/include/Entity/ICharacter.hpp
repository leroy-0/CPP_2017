//
// Created by Sebastien on 16/01/2018.
//

#ifndef R_TYPE_ACHARACTER_HPP
#define R_TYPE_ACHARACTER_HPP


#include "Entity.hpp"
#include "IProjectile.hpp"

class ICharacter : public Entity {
public:
    ICharacter();
    virtual ~ICharacter() = default;

    virtual IProjectile   &getProjectile() = 0;
};


#endif //R_TYPE_ACHARACTER_HPP
