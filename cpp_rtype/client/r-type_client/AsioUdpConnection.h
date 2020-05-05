#pragma once

#include <boost/asio.hpp>
#include <array>
#include <thread>
#include "IConnection.h"
#include "LockedQueue.h"

using boost::asio::ip::udp;

static const int NetworkBufferSizeUdp = 4096;

#define secure_code "epibro";

class AsioUdpConnection : public IConnection
{
public:
	AsioUdpConnection(const std::string & host, unsigned short server_port, unsigned short local_port = 0);
	virtual ~AsioUdpConnection();

	void Send(const std::string& message) override;
	bool HasMessages() override;
	std::string GetOneMessage() override;
	bool		isReady() const override;

private:
	bool					ready;
	boost::asio::io_service io_service;
	udp::socket socket;
	udp::endpoint server_endpoint;
	udp::endpoint remote_endpoint;
	std::array<char, NetworkBufferSizeUdp> recv_buffer;
	std::thread service_thread;

	LockedQueue<std::string> incomingMessages;

	void start_receive();
	void handle_receive(const std::error_code& error, std::size_t bytes_transferred);
	void run_service();

	AsioUdpConnection(AsioUdpConnection&);
};