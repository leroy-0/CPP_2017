//
// Created by longle-h on 17/01/18.
//

#ifndef R_TYPE_ROOM_HPP
#define R_TYPE_ROOM_HPP


#include <memory>
#include <Other/ILoader.hpp>
#include "Manager/Manager.hpp"
#include "Network/Network.hpp"
#include "Entity/IEnemy.hpp"
#include "Entity/IProjectile.hpp"
#include "Clock.hpp"
#include "Entity/PlayerEngine.hpp"
#include "Entity/Entity.hpp"
#include "Network/IConnection.hpp"

class Room {
public:
    Room() = default;
    Room(int, std::string , unsigned , unsigned);
    Room(const Room && r);
    virtual ~Room() = default;

    std::vector<PlayerEngine> getPlayers() const;
    int                 getPlaceLeft() const;
    bool                addPlayer(PlayerEngine &player);
    bool                removePlayer(std::string uuid);
    unsigned            getTcpPort() const;
    unsigned            getUdpPort() const;
    bool                checkRoom();
    void                setRoomId(unsigned id);
    unsigned            getRoomId() const;
    void                startGame(Manager & m);
    void                setEnemies(std::vector<IEnemy *> );
    std::vector<IEnemy *> & getEnemies();

private:
    std::vector<PlayerEngine>                              _players;
    std::vector<IEnemy *>                                    _enemies;
    std::vector<IProjectile>                               _projectiles;
    std::unique_ptr<IConnection>                           communicationUDP;
    std::unique_ptr<IConnection>                           communicationTCP;
    Clock                                                   _time;
    int                                                     nbPlace;
    unsigned                                                TCPport;
    unsigned                                                UDPport;
    unsigned                                                roomId;


    bool checkIfPlayerIsInRoom(const std::string &uuid) const;
    void sendPortUdp(unsigned int socketId);
    void sendStatusAllPlayers();
    void sendAllPlayersUUID();
    void movePlayer(Epibros::Direction direction, std::string message, unsigned int socketId, Manager &m);
    void manageNewPlayerInRoom(std::string string, unsigned int i);
    void sendAllEntitiesToRoom();
    void shot(std::string message, unsigned int socketId);
    void removeDeadEntities();
};


#endif //R_TYPE_ROOM_HPP
