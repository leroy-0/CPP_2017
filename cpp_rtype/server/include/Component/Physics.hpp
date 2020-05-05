//
// Created by Sebastien on 12/01/2018.
//

#ifndef R_TYPE_PHYSICS_HPP
#define R_TYPE_PHYSICS_HPP

#include "Rules.hpp"

namespace Component {
    struct Physics {
        Physics() : Enemy(false), Player(false), serverSide(false), direction(Epibros::Direction::UNKNOWN){};
        bool Enemy;
        bool Player;
        bool serverSide;
        Epibros::Direction direction;
    };
}


#endif //R_TYPE_PHYSICS_HPP
