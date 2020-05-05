//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_AGAME_HPP
#define R_TYPE_AGAME_HPP

#include "Room/Room.hpp"
#include "Engine.hpp"
#include <memory>

class AGame {
public:
    AGame(const std::string &ip, int port);
    virtual ~AGame() = default;

    virtual void run() = 0;

protected:
    Engine      gameEngine;
    std::unique_ptr<IConnection> Server;
    std::vector<Room *>   _rooms;
};


#endif //R_TYPE_AGAME_HPP
