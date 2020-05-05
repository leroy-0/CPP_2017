//
// Created by longle_h on 28/09/2017.
//

#ifndef PROJECT_ASERVER_HPP
#define PROJECT_ASERVER_HPP

#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "ClientTcpConnection.hpp"
#include "IDBManager.hpp"
#include "EOpenSSL.hpp"

using boost::asio::ip::tcp;

//-> Creation d'un client
//-> Read d'un client
//->

namespace spider {
    class AServer {
    public:
        AServer(boost::asio::io_service &io_service, unsigned short port);
        virtual ~AServer();

    private:
        std::vector<spider::ClientTcpConnection::pointer> clients;
        unsigned short port;
        tcp::acceptor accept;
        boost::asio::io_service & io_serv;
        IDBManager *dbManager;

    public:
        void createClient();
        virtual void run();
    };
}

#endif //PROJECT_ASERVER_HPP
