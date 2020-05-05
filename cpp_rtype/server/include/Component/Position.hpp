//
// Created by Sebastien on 12/01/2018.
//

#ifndef R_TYPE_UI_HPP
#define R_TYPE_UI_HPP

#include <vector>

namespace Component {
    struct Position {
        enum Geolocalisation
        {
            LEFT_UP,
            RIGHT_UP,
            LEFT_DOWN,
            RIGHT_DOWN
        };
        int x;
        int y;
        std::vector<Component::Position::Geolocalisation> posInMap;
    };
}


#endif //R_TYPE_UI_HPP
