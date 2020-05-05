#pragma once
#include	<thread>
#include	<iostream>
#include	<map>
#include	<boost/asio/buffer.hpp>
#include	<array>
#include	<boost/asio.hpp>
#include	<ctime>
#include	<string>
#include	<boost/bind.hpp>
#include	<boost/asio.hpp>
#include	"Network/AsioTcpSession.hpp"
#include	"Network/IConnection.hpp"
#include	"Network/locked_queue.hpp"
#define		B_SIZE 4096

using boost::asio::ip::tcp;

typedef std::map<unsigned int, AsioTcpSession::pointer>		ClientTcpMap;
typedef ClientTcpMap::value_type							ClientTcp;

class AsioTcpConnection : public IConnection {
public:
	AsioTcpConnection(unsigned short local_port);
	virtual ~AsioTcpConnection();
	bool										checkMessages();
	ClientMessage								getMessages();
	void										sendMessage(std::string message, unsigned int clientID);
	void										sendMessageAll(std::string message);
	bool										clientConnected();

public:
	void										wait();

private:
	void										start_accept();
	void										handle_accept(AsioTcpSession::pointer new_connection, const boost::system::error_code& error);
	void										run_service();

private:
	boost::asio::io_service						io_service;
	tcp::acceptor								acceptor;
	std::thread									service_thread;
	std::queue<ClientMessage>					messages;
	ClientTcpMap								clients;
	unsigned int								nextClientID;
};