//
// Created by longle-h on 17/01/18.
//

#include "Network/ConnectionCreate.hpp"
#include "AGame.hpp"

AGame::AGame(const std::string &ip, int port) : gameEngine() {
    this->Server = ConnectionCreate::createTcpConnection(port);
}
