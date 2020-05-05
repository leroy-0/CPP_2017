//
// Created by longle_h on 04/10/2017.
//

#ifndef PROJECT_DBMONGO_HPP
#define PROJECT_DBMONGO_HPP

#include "IDBManager.hpp"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

namespace spider
{
    class DBMongo : public IDBManager
    {
    public:
        DBMongo();
        ~DBMongo();

        bool init() const;
        bool insert(const std::string & _ip) const;
        bool insert(const std::string & _filename, const std::string & _idClient) const;
        bool findClient(const std::string & ip) const;
        bool updateClient(const std::string & _ip, bool online) const;
        std::string getIdClient(const std::string & _ip) const;

    };
}
#endif //PROJECT_DBMONGO_HPP
