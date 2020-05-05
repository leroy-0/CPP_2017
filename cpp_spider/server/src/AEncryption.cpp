//
// Created by Yan on 10/2/2017.
//

#include <AEncryption.hpp>

spider::AEncryption::AEncryption() :
    active(false), ip("") { }

spider::AEncryption::~AEncryption() {}

const std::string       spider::AEncryption::init(const std::string & ip)
{
    (void)ip;
    std::cout << "No encryption in place" << std::endl;
    return ("0001 No encryption in place\n");
}

const std::string       spider::AEncryption::encrypt(const std::string & message) const
{
    return (message);
}

const std::string       spider::AEncryption::decrypt(const std::string & message) const
{
    return (message);
}