//
// Created by longle_h on 04/10/2017.
//

#include "DBMongo.hpp"
#include "Tools.hpp"
#include <ctime>
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

spider::DBMongo::DBMongo() : IDBManager() {}

spider::DBMongo::~DBMongo() {}

bool                        spider::DBMongo::init() const
{
    mongocxx::instance  inst{};
    return (true);
}


bool                        spider::DBMongo::findClient(const std::string &ip) const
{
    mongocxx::client conn{mongocxx::uri{}};
    mongocxx::database db = conn["Spider"];
    mongocxx::collection coll = db["Users"];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            coll.find_one(document{} << "ip" << ip << finalize);
    if(maybe_result) {
        Tools::printServerLogClassic("Client found in Mongo", ip);
        return (true);
    }
    Tools::printServerLogClassic("Client not found in Mongo", ip);
    return (false);
}

bool                        spider::DBMongo::insert(const std::string & _filename,
                                                    const std::string & _idClient) const
{
    mongocxx::client conn{mongocxx::uri{}};
    mongocxx::database db = conn["Spider"];
    mongocxx::collection coll = db["Logs"];

    auto builder = bsoncxx::builder::stream::document{};
    Tools::printServerLogClassic("Starting insertion(logs) in Mongo", "Server");
    bsoncxx::document::value doc_value = builder
            << "idClient" << _idClient
            << "filePath" << _filename
            << bsoncxx::builder::stream::finalize;
    coll.insert_one(doc_value.view());
    Tools::printServerLogGreen("Mongo inset (logs) : successfull", "Server");
    return (true);
}

bool                        spider::DBMongo::insert(const std::string & _ip) const
{
    mongocxx::client        conn{mongocxx::uri{}};
    mongocxx::database      db;
    mongocxx::collection    coll;
    std::time_t             result;

    db = conn["Spider"];
    coll = db["Users"];
    result = std::time(nullptr);
    auto builder = bsoncxx::builder::stream::document{};

    Tools::printServerLogClassic("Starting insertion in Mongo", _ip);
    bsoncxx::document::value doc_value = builder
            << "ip" << _ip
            << "Last Connexion" << static_cast<long>(result)
            << "Online" << true
            << bsoncxx::builder::stream::finalize;
    coll.insert_one(doc_value.view());
    Tools::printServerLogGreen("Mongo insert (client) : successful", _ip);
    return (true);
}

bool                        spider::DBMongo::updateClient(const std::string & _ip,
                                                          bool online) const
{
    mongocxx::client        conn{mongocxx::uri{}};
    mongocxx::database      db;
    mongocxx::collection    coll;
    std::time_t             result;

    db = conn["Spider"];
    coll = db["Users"];
    result = std::time(nullptr);
    Tools::printServerLogClassic("Starting updating client", _ip);
    coll.update_one(document{} << "ip" << _ip << finalize,
                          document{} << "$set" << open_document <<
                                     "Last Connexion" << static_cast<long>(result)
                                     << "Online"<< online << close_document << finalize);
    Tools::printServerLogGreen("Updating client : successfull", _ip);
    return (true);
}

std::string                 spider::DBMongo::getIdClient(const std::string & _ip) const
{
    mongocxx::client        conn{mongocxx::uri{}};
    mongocxx::database      db;
    mongocxx::collection    coll;
    size_t                  pos_oid;
    size_t                  pos_first_guillemet;
    size_t                  pos_last_guillemet;
    std::string             id;
    bsoncxx::stdx::optional<bsoncxx::document::value>   result;

    db = conn["Spider"];
    coll = db["Users"];
    result = coll.find_one(document{} << "ip" << _ip << finalize);
    std::string doc = bsoncxx::to_json(*result);
    pos_oid = doc.find("$oid");
    pos_first_guillemet = doc.find_first_of("\"", pos_oid + 5);
    pos_last_guillemet = doc.find_first_of("\"", pos_first_guillemet + 1);
    id = doc.substr(pos_first_guillemet + 1, pos_last_guillemet - pos_first_guillemet - 1);
    return (id);
}