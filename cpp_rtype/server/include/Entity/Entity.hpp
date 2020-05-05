//
// Created by longle-h on 15/01/18.
//

#ifndef R_TYPE_ENTITY_HPP
#define R_TYPE_ENTITY_HPP

#include <string>
#include <unordered_map>
#include "Component/Position.hpp"
#include "Component/Physics.hpp"
#include "Component/Collider.hpp"

class Entity {
public:
    //CTOR/DTOR
    Entity();
    virtual ~Entity() = default;
    Entity &operator=(Entity dest);
    bool operator==(Entity dest);

    //Getter
    Component::Position         &getPosition();
    Component::Physics          &getPhysics();
    Component::Collider         &getCollider();
    std::string                 getUuid() const;
    bool                        isDead() const;
    int                         getSpeed() const;
    int                         getCodeSprite() const;

    //Setter
    void                        setPosition(Component::Position src);
    void                        setPosition(int x, int y);
    void                        setDead(bool);
    void                        setSpeed(int speed);
    void                        setCodeSprite(int code);

    //Function
    void                        updatePositionInMap();
    void                        regenerateUuid();

protected:
    Component::Position         position;
    Component::Physics          physics;
    Component::Collider         collider;
    std::string                 _uuid;
    bool                        dead;
    int                         speed;
    int                         codeSprite;
};

//Operator Overwrite


#endif //R_TYPE_ENTITY_HPP
