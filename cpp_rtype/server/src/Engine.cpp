//
// Created by Sebastien on 12/01/2018.
//

#include <iostream>
#include "Engine.hpp"
#include <thread>


void Engine::start(Room *r) {
    std::thread t(&launchThread, std::ref(*this), r);

    t.detach();
}

void Engine::launchThread(Engine &e, Room *r) {
    r->startGame(e.getManager());
    std::cout << "Je quitte le thread" << std::endl;
}



Manager &Engine::getManager() {
    return this->m;
}


