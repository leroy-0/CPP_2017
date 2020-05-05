//
// Created by Yan on 10/2/2017.
//

#include "stdafx.h"
#include "AEncryption.hpp"

spider::AEncryption::AEncryption() :
    active(false), ip("") { }

spider::AEncryption::~AEncryption() {}

void                    spider::AEncryption::init(std::string const & key)
{
    (void)key;
}

const std::string       spider::AEncryption::encrypt(std::string const & message) const
{
    return (message);
}

const std::string       spider::AEncryption::decrypt(std::string const & message) const
{
    return (message);
}