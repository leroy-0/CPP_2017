//
// Created by longle-h on 15/01/18.
//

#ifndef RULES_RTYPE_HPP
#define RULES_RTYPE_HPP

#include <vector>

#define MAX_HEIGHT  720
#define MAX_WIDTH   1280

namespace Epibros {

    struct Message {
        char             magicNber[7];
        int              timestamp;
        int              code;
        char             _mess[4096];
    };

    enum Direction {
        FORWARD,
        FORWARD_UP, //Up_Right
        FORWARD_DOWN, //Down_Right
        BACKWARD,
        BACKWARD_UP, //Up_Left
        BACKWARD_DOWN, // Down_Left
        UP,
        DOWN,
        UNKNOWN
    };

    struct Pattern {
        Pattern(int _x, int _y)
        {
            x = _x;
            y = _y;
        };
        int x;
        int y;
    };

    struct SwarmPattern {
        SwarmPattern() = default;
        int     nbShip;
        std::vector<struct Epibros::Pattern *> patternContainer;
    };
};


#endif //RULES_RTYPE_HPP
