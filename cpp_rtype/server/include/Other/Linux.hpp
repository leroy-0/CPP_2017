//
// Created by Sébastien on 20/01/2018.
//

#ifndef R_TYPE_LINUX_HPP
#define R_TYPE_LINUX_HPP

#include        <string>
#include "../../ia/IAi.hpp"
#include "ILoader.hpp"

class Linux : public ILoader {
public:
    Linux() = default;
    virtual ~Linux() = default;

    IAi *loadSharedLibrary(const std::string &);

protected:
};


#endif //R_TYPE_LINUX_HPP
