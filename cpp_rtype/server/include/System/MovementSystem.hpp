//
// Created by Sebastien on 15/01/2018.
//

#ifndef R_TYPE_INPUTMANAGER_HPP
#define R_TYPE_INPUTMANAGER_HPP

#include "Entity/Entity.hpp"
#include "Entity/IEnemy.hpp"
#include "ASystem.hpp"
#include "Rules.hpp"

class MovementSystem : public ASystem  {
public:
    //CTOR/DTOR
    MovementSystem() = default;
    virtual ~MovementSystem() = default;

    bool        moveEntity(Epibros::Direction direction, Entity &e) const;
    bool        moveEntity(Epibros::Direction direction, IEnemy *) const;

};

#endif //R_TYPE_INPUTMANAGER_HPP
