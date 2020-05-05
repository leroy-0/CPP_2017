//
// Created by Sebastien on 12/01/2018.
//

#ifndef R_TYPE_ENGINE_HPP
#define R_TYPE_ENGINE_HPP

#include <thread>
#include "Room/Room.hpp"
#include "Manager/Manager.hpp"
#include "Network/Network.hpp"
#include "Entity/Entity.hpp"
#include "Clock.hpp"

class Engine {
public:
    Engine() = default;
    ~Engine() = default;

    void            start(Room * r);
    static void     launchThread(Engine& e, Room * r);
    Manager         &getManager();

private:
    Manager         m;

};


#endif //R_TYPE_ENGINE_HPP
