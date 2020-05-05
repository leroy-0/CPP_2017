//
// Created by longle-h on 17/01/18.
//

#include <iostream>
#ifdef _WIN32
    #include <Other/Windows.hpp>
#elif (__linux__)
    #include "Other/Linux.hpp"
#endif
#include "Rules.hpp"
#include "Other/Parse.hpp"
#include "Rtype.hpp"

Rtype::Rtype(const std::string &ip, unsigned port) : AGame(ip, port) {
    this->portNb = port;
#ifdef _WIN32
    load = new Windows();
#elif __linux__
    load = new Linux();
#endif
}

void Rtype::run() {
    bool running = true;
    while (running)
    {
        if (this->Server->checkMessages())
        {
            ClientMessage mess = this->Server->getMessages();
            int nbRFC = Parse::checkRFCNumber(mess.first);
            std::stringstream ss;
            ss << mess.second;
            std::cout << "Message Received from " << ss.str() << " : " << mess.first << std::endl;
            switch (nbRFC)
            {
                case 101:
                    this->sendListOfRoom(mess.second);
                    break;
                case 108:
                    this->createRoom(mess.second);
                    break;
                case 109:
                    this->joinRoomParse(mess.first, mess.second);
                    break;
                default:
                    this->Server->sendMessage("301 are you dumb\n", mess.second);
                    break;
            }
            if (mess.first == "EXIIIIIIT") {
                running = false;
                break;
            }
        }
        for (auto &room : this->_rooms) {
            if (!room->checkRoom())
                this->deleteAndStartRoom(room->getRoomId());
        }
    }
}

void Rtype::sendListOfRoom(unsigned socketId) {
    PlayerEngine p;
    std::stringstream ss;
    std::string mess;
    unsigned index = 0;

    ss << "107 ";
    for (auto &room : this->_rooms)
    {
        if (room->getPlaceLeft() != 0) {
            ss << index << "," << room->getPlaceLeft();
            if (index != (this->_rooms.size() - 1))
                ss << ":";
        }
        index++;
    }
    ss << std::endl;
    mess = ss.str();
    this->Server->sendMessage(mess, socketId);
}

void Rtype::createRoom(unsigned socketId) {
    unsigned portTcp = this->portNb + 1;
    unsigned portUdp = this->portNb + 2;
    this->portNb = portUdp;
    this->_rooms.push_back(new Room(4, "localhost", portTcp, portUdp));
    this->_rooms.back()->setRoomId(static_cast<unsigned int>(this->_rooms.size() - 1));
    this->createEnemies();
    this->_rooms.back()->setEnemies(allEnnemies);
    this->joinRoom(static_cast<unsigned int>(this->_rooms.size() - 1), socketId);
}

void Rtype::joinRoom(unsigned int roomId, unsigned int socketId) {
    PlayerEngine p;
    std::stringstream  ss;

    if (this->_rooms.size() == 0 || roomId > (this->_rooms.size() - 1))
    {
        this->Server->sendMessage("302 Room doesn't exist\n", socketId);
        return;
    }
    if (this->_rooms.at(roomId)->getPlaceLeft() > 0) {
        p.setPosition(this->getPositionForPlayer(this->_rooms.at(roomId)));
        p.setSpeed(8);
        p.getCollider().size_y = 25;
        p.getCollider().size_x = 65;
        p.getProjectile().setSpeed(30);
        this->_rooms.at(roomId)->addPlayer(p);
        ss << "102 IP:" << this->_rooms.at(roomId)->getTcpPort() << ":" << p.getUuid() << std::endl;
        this->Server->sendMessage(ss.str(), socketId);
    } else {
        this->Server->sendMessage("302 Room doesn't exist\n", socketId);
        return;
    }
}

void Rtype::joinRoomParse(std::string message, unsigned int socketId) {
    std::vector<std::string> tokens = Parse::split(message, ' ');
    if (tokens.size() != 2 || tokens.at(1).compare("\n") == 0)
    {
        this->Server->sendMessage("303 Precise a Room\n", socketId);
        return;
    }

    int                      roomId = static_cast<int>(std::atol(tokens.at(1).c_str()));
    this->joinRoom(static_cast<unsigned int>(roomId), socketId);
}

void Rtype::deleteAndStartRoom(unsigned int roomId) {
    unsigned index = 0;
    for (auto &room: this->_rooms) {
        if (room->getRoomId() == roomId)
            break;
        index++;
    }
    Room * r = this->_rooms.at(index);
    this->_rooms.erase(this->_rooms.begin() + index);
    this->gameEngine.start(r);
}

Component::Position Rtype::getPositionForPlayer(Room *&r) {
    unsigned nbPlayer = r->getPlayers().size();
    Component::Position new_pos;

    switch (nbPlayer) {
        case 0:
            new_pos.x = MAX_WIDTH * 1/20;
            new_pos.y = 0;
            break;
        case 1:
            new_pos.x = MAX_WIDTH * 1/20;
            new_pos.y = MAX_HEIGHT * 1/4;
            break;
        case 2:
            new_pos.x = MAX_WIDTH * 1/20;
            new_pos.y = MAX_HEIGHT * 2/4;
            break;
        case 3:
            new_pos.x = MAX_WIDTH * 1/20;
            new_pos.y = MAX_HEIGHT * 3/4;
            break;
        default:
            new_pos.x = 0;
            new_pos.y = 0;
            break;
    }

    return new_pos;
}

void Rtype::createEnemies() {
    int waitTime = 0;

    IEnemy *_new = new IEnemy();
    _new->ai = load->loadSharedLibrary("basicShip");

    for (unsigned int i = 0; i < _new->ai->getSwarmPattern()->nbShip ; i++) {
        IEnemy *toAdd = new IEnemy();

        toAdd->ai = load->loadSharedLibrary("basicShip");
        int x = toAdd->ai->getSwarmPattern()->patternContainer.at(i)->x;
        int y = toAdd->ai->getSwarmPattern()->patternContainer.at(i)->y;
        toAdd->ai->setWaitTime(waitTime);
        toAdd->getCollider().size_x = 40;
        toAdd->getCollider().size_y = 40;
        toAdd->setPosition(MAX_WIDTH + (x * 100), MAX_HEIGHT / 2 + (y * 50));
        allEnnemies.push_back(toAdd);
        waitTime += 2;
    }
}