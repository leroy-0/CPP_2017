#pragma once
#include	<thread>
#include	<iostream>
#include	<map>
#include	<boost/asio/buffer.hpp>
#include	<array>
#include	<boost/asio.hpp>
#include	"IConnection.hpp"
#include	"locked_queue.hpp"
#define		B_SIZE 4096

using boost::asio::ip::udp;

typedef std::map<unsigned int, udp::endpoint>			ClientMap;
typedef ClientMap::value_type							Client;

class AsioUdpConnection : public IConnection {
public:
	AsioUdpConnection(unsigned short local_port);
	virtual ~AsioUdpConnection();
	bool								checkMessages();
	bool								clientConnected();
	ClientMessage						getMessages();
	void								sendMessage(std::string message, unsigned int clientID);
	void								sendMessageAll(std::string message);

public:
	static std::unique_ptr<AsioUdpConnection>		createConnection(unsigned int port);
	void										wait();

private:
	AsioUdpConnection(AsioUdpConnection&);
	void						start_receive();
	void						handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
	void						handle_send(std::string, const boost::system::error_code&, std::size_t) {}
	void						run_service();
	unsigned int				getId(udp::endpoint endpoint);
	void						send(std::string pmessage, udp::endpoint target_endpoint);
	
private:
	boost::asio::io_service		io_service;
	udp::socket					socket;
	udp::endpoint				remote_endpoint;
	std::array<char, B_SIZE>	recv_buffer;
	std::thread					service_thread;
	locked_queue<ClientMessage> messageQueue;
	ClientMap					clients;
	unsigned int			nextClientID;
};