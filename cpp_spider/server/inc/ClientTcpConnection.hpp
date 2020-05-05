//
// Created by longle_h on 28/09/2017.
//

#ifndef PROJECT_CLIENT_HPP
#define PROJECT_CLIENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <map>
#include "EOpenSSL.hpp"
#include "Log.hpp"
#include "IDBManager.hpp"

#define MAX_LEN         256

using boost::asio::ip::tcp;

namespace spider {
    class ClientTcpConnection : public std::enable_shared_from_this<spider::ClientTcpConnection> {
    public:
        typedef std::shared_ptr<spider::ClientTcpConnection> pointer;
        typedef bool (spider::ClientTcpConnection::*func)();
        static pointer create(boost::asio::io_service& ios, AEncryption *, IDBManager *db);
        enum    state
        {
            CONNEXION,
            WAITING_FILE,
            RCV_FILE
        };

        ClientTcpConnection(boost::asio::io_service & io_service, AEncryption *, IDBManager *db);
        virtual ~ClientTcpConnection();
        void            setIp(const std::string);
        std::string     getIp() const;
        void            init();
        void            setId(std::string id);
        const           std::string getId() const;
        tcp::socket     socket;
        Log             log;

    private:
        std::string                                         m_mess;
        std::string                                         m_id;
        boost::array<char, MAX_LEN>                         buf;
        std::string                                         ip;
        AEncryption                                         *rsa;
        state                                               _state;
        std::map<spider::ClientTcpConnection::state, func>  request;
        IDBManager                                          *db;
        boost::array<char, MAX_LEN>                         final_buf;

        void handleWrite(const boost::system::error_code& error);
        void handleRead(const boost::system::error_code& error);
        void listenRead();
        void closeConnection();
        bool handleConnexionState();
        bool handleWaitingFileState();
        bool handleRcvFileState();
    };
}

#endif //PROJECT_CLIENT_HPP
