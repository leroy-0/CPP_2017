//
// Created by longle-h on 17/01/18.
//

#include <vector>
#include <algorithm>
#include "Other/Parse.hpp"
#include "Network/ConnectionCreate.hpp"
#include "Room/Room.hpp"

std::vector<PlayerEngine> Room::getPlayers() const {
    return this->_players;
}

int Room::getPlaceLeft() const {
    return static_cast<int>(this->nbPlace - this->_players.size());
}

bool Room::addPlayer(PlayerEngine &player) {
    if (this->getPlaceLeft() > 0) {
        this->_players.push_back(player);
        return true;
    }
    return false;
}

Room::Room(int placeMax, std::string ip, unsigned portUDP, unsigned portTCP)
        : nbPlace(placeMax), _time(Clock()) {
    this->communicationTCP = ConnectionCreate::createTcpConnection(portTCP);
    this->communicationUDP = ConnectionCreate::createUdpConnection(portUDP);
    this->TCPport = portTCP;
    this->UDPport = portUDP;
}

bool Room::removePlayer(std::string uuid) {
    int index = 0;
    for (auto player = this->_players.begin(); player < this->_players.end(); ++player) {
        if ((*player).getUuid() == uuid) {
            this->_players.erase(_players.begin() +  index);
            return true;
        }
        index++;
    }
    return false;
}

unsigned Room::getTcpPort() const {
    return this->TCPport;
}

unsigned Room::getUdpPort() const {
    return this->UDPport;
}

Room::Room(const Room &&r) : nbPlace(r.getPlaceLeft()), _time(Clock()) {
    this->communicationTCP = ConnectionCreate::createTcpConnection(r.getTcpPort());
    this->communicationUDP = ConnectionCreate::createUdpConnection(r.getUdpPort());
    this->TCPport = r.getTcpPort();
    this->UDPport = r.getUdpPort();
}

bool Room::checkRoom() {
    if (this->communicationTCP->checkMessages())
    {
        ClientMessage mess = this->communicationTCP->getMessages();
        int nbRFC = Parse::checkRFCNumber(mess.first);
        std::stringstream ss;
        ss << mess.second;
        std::cout << "Message Received (Room) from " << ss.str() << " : " << mess.first << std::endl;
        switch (nbRFC){
            case 110:
                this->manageNewPlayerInRoom(mess.first, mess.second);
                break;
            case 111:
                this->communicationTCP->sendMessageAll("106 START\n");
                return false;
            default:
                this->communicationTCP->sendMessage("301 are you dumb\n", mess.second);
                break;
        }

    }
    return true;
}

void Room::sendPortUdp(unsigned int socketId) {
    std::stringstream ss;

    ss << "103 IP:" << this->getUdpPort() << std::endl;

    this->communicationTCP->sendMessage(ss.str(), socketId);
}

void Room::setRoomId(unsigned id) {
    this->roomId = id;
}

unsigned Room::getRoomId() const {
    return this->roomId;
}

void Room::startGame(Manager &m) {
    bool running = true;
    this->sendStatusAllPlayers();
    int  sendInfo = 0;
    while (running) {
        if (!this->communicationTCP->clientConnected())
            return;
        if (this->communicationUDP->checkMessages())
        {
            auto mess = this->communicationUDP->getMessages();
            int RFC = Parse::checkRFCNumber(mess.first);
            switch (RFC)
            {
                case 401:
                    this->movePlayer(Epibros::UP, mess.first, mess.second, m);
                    break;
                case 402:
                    this->movePlayer(Epibros::DOWN, mess.first, mess.second, m);
                    break;
                case 403:
                    this->movePlayer(Epibros::BACKWARD, mess.first, mess.second, m);
                    break;
                case 404:
                    this->movePlayer(Epibros::FORWARD, mess.first, mess.second, m);
                    break;
                case 408:
                    this->shot(mess.first, mess.second);
                    break;
                default:
                    this->communicationUDP->sendMessage("301 are you dumb\n", mess.second);
                    break;
            }
        }
        if (sendInfo == 150000) {
            m.getIaSystem().manageIA(_enemies, m.getMovementSystem(), this->_players, this->_projectiles, m.getColliderSytem());
            m.getServerSideManager().manageServerSideEntities(this->_projectiles, m.getMovementSystem());
            this->removeDeadEntities();
            this->sendAllEntitiesToRoom();
            sendInfo = 0;
        }
        else
            sendInfo++;
    }
}

void Room::sendStatusAllPlayers() {
    std::stringstream ss;
    unsigned long index = 0;
    ss << "406 ";
    for (auto &player : this->_players)
    {
        ss << player.getUuid() << "," << player.getPosition().x << "," << player.getPosition().y;
        if (index != (this->_players.size() - 1))
            ss << ":";
        index++;
    }
    ss << std::endl;
    std::cout << "(Thread) " << ss.str() << std::endl;
    this->communicationTCP->sendMessageAll(ss.str());
}

void Room::sendAllPlayersUUID() {
    std::stringstream ss;
    unsigned long index = 0;
    ss << "105 ";
    for (auto &player : this->_players) {
        ss << player.getUuid();
        if (index != (this->_players.size() - 1))
            ss << ":";
        index++;
    }
    ss << std::endl;
    this->communicationTCP->sendMessageAll(ss.str());
}

void Room::movePlayer(Epibros::Direction direction, std::string message, unsigned int socketId, Manager &m) {
    //Check le uuid
    //Token[0] == nb
    //Token[1] == uuid
    std::vector<std::string> tokens = Parse::split(message, ' ');
    if (tokens.size() != 2)
    {
        this->communicationUDP->sendMessage("303 Not enough arguments\n", socketId);
        return;
    }
    if (this->checkIfPlayerIsInRoom(tokens.at(1))) {
        for (auto &player : this->_players)
        {
            if (player.getUuid() == tokens.at(1)) {
                m.getMovementSystem().moveEntity(direction, player);
                m.getColliderSytem().checkCollision(this->_enemies, player);
                m.getColliderSytem().checkCollision(this->_projectiles, player);
            }
        }
    } else {
        this->communicationUDP->sendMessage("304 You're not in this room you cheater\n", socketId);
    }
}

bool Room::checkIfPlayerIsInRoom(const std::string &uuid) const {
    for (auto &player : this->_players) {
        if (player.getUuid() == uuid)
            return true;
    }

    return false;
}

void Room::manageNewPlayerInRoom(std::string message, unsigned int socketId) {
    std::vector<std::string> tokens = Parse::split(message, ' ');
    if (tokens.size() != 2)
    {
        this->communicationTCP->sendMessage("303 Not enough arguments\n", socketId);
        return;
    }
    if (!this->checkIfPlayerIsInRoom(tokens.at(1))) {
        this->communicationTCP->sendMessage("304 You're not in this room\n", socketId);
        return;
    }
    this->sendPortUdp(socketId);
    this->sendAllPlayersUUID();
}

void Room::sendAllEntitiesToRoom() {
    std::stringstream ss;
    unsigned long index = 0;

    ss << "407 ";
    for (auto &player : this->_players) {
        ss << player.getUuid() << "," << player.getPosition().x << "," << player.getPosition().y << ",player,"
                << player.getCodeSprite() ;
        if (index != (this->_players.size() - 1))
            ss << ":";
        index++;
    }
    if (!this->_enemies.empty())
    {
        index = 0;
        ss << ":";
        for (auto &enemy : this->_enemies) {
            ss << enemy->getUuid() << "," << enemy->getPosition().x << "," << enemy->getPosition().y
               << ",enemy," << enemy->getCodeSprite();
            if (index != (this->_enemies.size() - 1))
                ss << ":";
            index++;
        }
    }
    if (!this->_projectiles.empty())
    {
        index = 0;
        ss << ":";
        for (auto &projectile : this->_projectiles) {
            ss << projectile.getUuid() << "," << projectile.getPosition().x << "," << projectile.getPosition().y
                    << ",projectile," << projectile.getCodeSprite();
            if (index != (this->_projectiles.size() - 1))
                ss << ":";
            index++;
        }
    }
    ss << "\n";
    std::cout << "All entities: " << ss.str();
    this->communicationUDP->sendMessageAll(ss.str());
}

void Room::setEnemies(std::vector<IEnemy *> allEnnemies) {
    _enemies = allEnnemies;
}

void Room::shot(std::string message, unsigned int socketId) {
    std::vector<std::string> tokens = Parse::split(message, ' ');
    if (tokens.size() != 2) {
        this->communicationTCP->sendMessage("303 Not enough arguments\n", socketId);
        return;
    }

    for (auto &player : this->_players) {
        if (player.getUuid() == tokens.at(1)) {
            int pos_x = player.getPosition().x + player.getCollider().size_x;
            int pos_y = player.getPosition().y + player.getCollider().size_y;
            IProjectile p(player.getProjectile());
            p.regenerateUuid();
            this->_projectiles.push_back(p);
            this->_projectiles.back().setPosition(pos_x, pos_y);
        }
    }
}

void Room::removeDeadEntities() {
    for (auto player = this->_players.begin(); player < this->_players.end(); player++) {
        if ((*player).isDead())
            this->_players.erase(player);
    }
    for (auto enemy = this->_enemies.begin(); enemy < this->_enemies.end(); enemy++) {
        if ((*enemy)->isDead())
            this->_enemies.erase(enemy);

    }
    for (auto proj = this->_projectiles.begin(); proj < this->_projectiles.end(); proj++) {
        if ((*proj).isDead())
            this->_projectiles.erase(proj);
    }
}

std::vector<IEnemy *> &Room::getEnemies() {
    return this->_enemies;
}
