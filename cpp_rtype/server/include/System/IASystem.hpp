//
// Created by Sebastien on 16/01/2018.
//

#ifndef R_TYPE_IASYSTEM_HPP
#define R_TYPE_IASYSTEM_HPP

#include <vector>
#include <Entity/IEnemy.hpp>
#include <Entity/PlayerEngine.hpp>
#include "System/MovementSystem.hpp"
#include "ASystem.hpp"

class IASystem : public ASystem {
public:
    IASystem() = default;
    virtual ~IASystem() = default;

    void    manageIA(std::vector<IEnemy *> &, MovementSystem, std::vector<PlayerEngine> p, std::vector<IProjectile> pr, ColliderSystem cs);
};


#endif //R_TYPE_IASYSTEM_HPP
