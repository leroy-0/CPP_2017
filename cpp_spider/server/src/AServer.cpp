//
// Created by longle_h on 29/09/2017.
//

#include "AServer.hpp"
#include "Log.hpp"
#include "DBMongo.hpp"

spider::AServer::AServer(boost::asio::io_service &io_service, unsigned short portArg) :
        port(portArg), accept(io_service, tcp::endpoint(tcp::v4(), port)), io_serv(io_service), dbManager(new spider::DBMongo())
{
    this->dbManager->init();
}

spider::AServer::~AServer() {}

void spider::AServer::createClient()
{
    this->clients.back()->init();
    auto it = this->clients.back();
    if (!this->dbManager->findClient((*it).getIp()))
        this->dbManager->insert((*it).getIp());
    else
        this->dbManager->updateClient((*it).getIp(), true);
    (*it).setId(this->dbManager->getIdClient((*it).getIp()));
    (*it).log.init((*it).getId());
    this->run();
}

void spider::AServer::run()
{
    this->clients.push_back(spider::ClientTcpConnection::create(this->io_serv, static_cast<AEncryption *>(new EOpenSSL()), this->dbManager));
    this->accept.async_accept(this->clients.back()->socket, boost::bind(&spider::AServer::createClient, this));
    this->io_serv.run();
}
