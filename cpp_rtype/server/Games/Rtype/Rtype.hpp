//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_RTYPE_HPP
#define R_TYPE_RTYPE_HPP

#include "Entity/IEnemy.hpp"
#include "../AGame.hpp"

class Rtype : public AGame {
public:
    Rtype(const std::string &ip, unsigned port);
    virtual ~Rtype() = default;

    void            run();

private:
    void            sendListOfRoom(unsigned socketId);
    void            createRoom(unsigned socketId);
    void            joinRoomParse(std::string message, unsigned int socketId);
    void            joinRoom(unsigned int roomId, unsigned int socketId);
    void            createEnemies();
    void            deleteAndStartRoom(unsigned int roomId);
    Component::Position getPositionForPlayer(Room *&r);
    std::vector<IEnemy *> allEnnemies;

    unsigned        portNb;
    ILoader         *load;
};


#endif //R_TYPE_RTYPE_HPP
