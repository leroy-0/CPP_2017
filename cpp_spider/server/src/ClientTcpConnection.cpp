//
// Created by longle_h on 29/09/2017.
//

#include "EOpenSSL.hpp"
#include "ClientTcpConnection.hpp"
#include <boost/date_time.hpp>
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

spider::ClientTcpConnection::ClientTcpConnection(boost::asio::io_service &io_service, spider::AEncryption * type, spider::IDBManager *db) :
        socket(io_service), rsa(type)
{
    this->_state = CONNEXION;
    this->request[spider::ClientTcpConnection::CONNEXION] = &spider::ClientTcpConnection::handleConnexionState;
    this->request[spider::ClientTcpConnection::WAITING_FILE] = &spider::ClientTcpConnection::handleWaitingFileState;
    this->request[spider::ClientTcpConnection::RCV_FILE] = &spider::ClientTcpConnection::handleRcvFileState;
    this->db = db;
}

spider::ClientTcpConnection::~ClientTcpConnection()
{}

spider::ClientTcpConnection::pointer spider::ClientTcpConnection::create(boost::asio::io_service &ios, spider::AEncryption * encryption, spider::IDBManager *db)
{
    return spider::ClientTcpConnection::pointer(new spider::ClientTcpConnection(ios, encryption, db));
}

void spider::ClientTcpConnection::setIp(const std::string ip)
{
    this->ip = ip;
}

void spider::ClientTcpConnection::handleRead(const boost::system::error_code &error)
{
  if (this->socket.is_open()) {
    if (!error) {
        (this->*request[this->_state])();
        if (!this->buf.empty()) {
                this->buf.assign(0);
            }
        this->listenRead();
        } else {
            if (this->socket.is_open())
                this->m_mess = "0003 I have a bad feeling about this!\n";
            std::cout << error.message() << std::endl;
            this->closeConnection();
        }
        boost::asio::async_write(this->socket, boost::asio::buffer(this->m_mess),
                                 boost::bind(&spider::ClientTcpConnection::handleWrite, this,
                                             boost::asio::placeholders::error));
    }
}

void spider::ClientTcpConnection::listenRead()
{
    if (this->socket.is_open()) {
        this->socket.async_read_some(boost::asio::buffer(this->buf, MAX_LEN),
                                     boost::bind(&spider::ClientTcpConnection::handleRead, shared_from_this(),
                                                 boost::asio::placeholders::error));
    }
}

void spider::ClientTcpConnection::closeConnection()
{
    this->socket.close();
    Tools::printServerLogRed("Client disconnected", this->ip);
    this->db->updateClient(this->ip, false);
}

void spider::ClientTcpConnection::handleWrite(const boost::system::error_code &error)
{
    if (this->socket.is_open()) {
        if (!error) {
            this->m_mess.clear();
            this->listenRead();
        } else {
            std::cout << error.message() << std::endl;
            this->closeConnection();
        }
    }
}

void spider::ClientTcpConnection::init()
{
    this->ip = this->socket.remote_endpoint().address().to_string();
    Tools::printServerLogGreen("Client connected", this->ip);
    this->m_mess = std::string("0001 the matrix is everywhere\r\n0006 " + this->rsa->init(this->socket.remote_endpoint().address().to_string()));
    this->buf.assign(0);
    this->rsa->encrypt("Hello World");
    boost::asio::async_write(this->socket, boost::asio::buffer(this->m_mess),
                             boost::bind(&spider::ClientTcpConnection::handleWrite, this,
                                         boost::asio::placeholders::error));
}

bool spider::ClientTcpConnection::handleConnexionState()
{
    if (!buf.empty() && buf.size() >= 4 && buf[0] == '0'
        && buf[1] == '0' && buf[2] == '0' && buf[3] == '2') {
        Tools::printServerLogGreen("Client is paired", this->ip);
        this->m_mess = "0002 Yes sir !\n";
        this->_state = WAITING_FILE;
    }
    else
    {
        Tools::printServerLogRed("Error while pairing client", this->ip);
        Tools::printServerLogClassic("Now closing connexion", this->ip);
        this->closeConnection();
        return false;
    }
    return true;
}

bool spider::ClientTcpConnection::handleRcvFileState()
{
    std::string		tmp;
    std::stringstream ss;
    int			i = 0;

    if (!buf.empty() && buf.size() >= 4 && buf[0] == '0'
        && buf[1] == '0' && buf[2] == '0' && buf[3] == '5') {
        //END OF RECEIVED FILE -> WRITE ON BD + FILE
        tmp = this->log.flush();
        this->db->insert(tmp, this->getId());
        this->_state = WAITING_FILE;
        this->m_mess = "0002 Yes sir\n";
    }
    else
    {
        while(i < MAX_LEN)
        {
            ss << this->buf[i];
            i++;
        }
        tmp = ss.str();
        tmp = this->rsa->decrypt(tmp);
        this->log.addData(tmp);
        this->m_mess = "0002 Yes sir\n";
    }
    return (true);
}

std::string spider::ClientTcpConnection::getIp() const
{
    return this->ip;
}

bool spider::ClientTcpConnection::handleWaitingFileState()
{
    if (!buf.empty() && buf.size() >= 4 && buf[0] == '0'
        && buf[1] == '0' && buf[2] == '0' && buf[3] == '4') {
        Tools::printServerLogClassic("Now receiving a file from the client", this->ip);
        this->_state = RCV_FILE;
        this->m_mess = "0002 Yes sir!\n";
    }
    else
    {
        Tools::printServerLogRed("Unrecognized command", this->ip);
        Tools::printServerLogClassic("Waiting for file", this->ip);
        this->m_mess = "0003 I have a bad feeling about this!\n";
        return false;
    }
    return true;
}

void spider::ClientTcpConnection::setId(std::string id)
{
    this->m_id = id;
}

const std::string spider::ClientTcpConnection::getId() const
{
    return this->m_id;
}