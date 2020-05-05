//
// Created by longle_h on 04/10/2017.
//

#ifndef PROJECT_ADBMANAGER_HPP
#define PROJECT_ADBMANAGER_HPP

#include <string>
#include <iostream>

namespace spider
{
    class IDBManager
    {
    public:
        IDBManager() {};
        virtual ~IDBManager() {};


        virtual bool init() const = 0;
        virtual bool insert(const std::string & _ip) const = 0;
        virtual bool insert(const std::string & _filename, const std::string & _idClient) const = 0;
        virtual bool findClient(const std::string & ip) const = 0;
        virtual bool updateClient(const std::string & _ip, bool online) const = 0;
        virtual std::string getIdClient(const std::string & _ip) const = 0;
    };
}

#endif //PROJECT_ADBMANAGER_HPP
