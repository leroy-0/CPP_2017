//
// Created by Yan on 10/2/2017.
//

#ifndef PROJECT_AENCRYPTION_HPP
#define PROJECT_AENCRYPTION_HPP

#include <iostream>
#include <string>

namespace spider {
    class AEncryption {
    public:
        AEncryption();
        virtual ~AEncryption();
        virtual void                    init(std::string const & key);
        virtual const std::string       encrypt(std::string const & ) const;
        virtual const std::string       decrypt(std::string const & ) const;

    protected:
        bool                            active;
        std::string                     ip;
    };
}

#endif //PROJECT_AENCRYPTION_HPP
