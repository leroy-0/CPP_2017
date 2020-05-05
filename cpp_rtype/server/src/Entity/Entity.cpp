//
// Created by longle-h on 15/01/18.
//

#include <Other/UuidGenerator.hpp>
#include "Entity/Entity.hpp"
#include "Other/Parse.hpp"

Entity::Entity() {
    dead = false;
    this->speed = 1;
    this->codeSprite = 1;
    this->position.x = 0;
    this->position.y = 0;
    this->collider.size_x = 1;
    this->collider.size_y = 1;
    _uuid = UuidGenerator::generateUUID();
}

Component::Position &Entity::getPosition() {
    return this->position;
}

void Entity::setPosition(Component::Position src) {
    this->position.x = src.x;
    this->position.y = src.y;
}

void Entity::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

Entity &Entity::operator=(Entity src) {
    setPosition(src.getPosition());
    return *this;
}

void Entity::updatePositionInMap() {
    int             state = 0;
    int             x = this->getPosition().x;
    int             y = this->getPosition().y;
    this->position.posInMap.clear();

    while (true) {
        switch (state)
        {
            case 1:
                x = this->position.x + this->collider.size_x;
                y = this->position.y;
                break;
            case 2:
                x = this->position.x;
                y = this->position.y + this->collider.size_y;
                break;
            case 3:
                x = this->position.x + this->collider.size_x;
                y = this->position.y + this->collider.size_y;
                break;
            case 4:
                return;
            default:
                break;
        }
        if (x <= (MAX_WIDTH / 2) && y <= (MAX_HEIGHT / 2) &&
                !Parse::findInVector(this->position.posInMap, Component::Position::LEFT_UP))
            this->position.posInMap.push_back(Component::Position::LEFT_UP);
        if (x <= (MAX_WIDTH / 2) && y > (MAX_HEIGHT / 2) &&
                !Parse::findInVector(this->position.posInMap, Component::Position::LEFT_DOWN))
            this->position.posInMap.push_back(Component::Position::LEFT_DOWN);
        if (x > (MAX_WIDTH / 2) && y > (MAX_HEIGHT / 2) &&
                !Parse::findInVector(this->position.posInMap, Component::Position::RIGHT_DOWN))
            this->position.posInMap.push_back(Component::Position::RIGHT_DOWN);
        if (x > (MAX_WIDTH / 2) && y <= (MAX_HEIGHT / 2) &&
                !Parse::findInVector(this->position.posInMap, Component::Position::RIGHT_UP))
            this->position.posInMap.push_back(Component::Position::RIGHT_UP);
        state++;
    }
}

Component::Physics &Entity::getPhysics() {
    return physics;
}

Component::Collider &Entity::getCollider() {
    return collider;
}

void Entity::setDead(bool d) {
    dead = d;
}

bool Entity::operator==(Entity dest) {
    return dest.getUuid() == _uuid;
}

std::string Entity::getUuid() const {
    return _uuid;
}

bool Entity::isDead() const {
    return this->dead;
}

int Entity::getSpeed() const {
    return this->speed;
}

void Entity::setSpeed(int sspeed) {
    this->speed = sspeed;
}

int Entity::getCodeSprite() const {
    return this->codeSprite;
}

void Entity::setCodeSprite(int code) {
    this->codeSprite = code;
}

void Entity::regenerateUuid() {
    this->_uuid = UuidGenerator::generateUUID();
}
