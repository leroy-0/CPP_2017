#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <thread>
#include "IConnection.h"
#include "LockedQueue.h"

using boost::asio::ip::tcp;

#define secure_code "epibro";

class AsioTcpConnection : public IConnection
{
public:
	AsioTcpConnection(const std::string & host, const std::string & port);
	virtual ~AsioTcpConnection();
	void stop();

	bool isReady() const override;
	void Send(const std::string& message) override;
	bool HasMessages() override;
	std::string GetOneMessage() override;

private:
	void start(tcp::resolver::iterator endpoint_iter);
	void start_connect(tcp::resolver::iterator endpoint_iter);
	void handle_connect(const boost::system::error_code& ec,
		tcp::resolver::iterator endpoint_iter);
	void start_read();
	void handle_read(const boost::system::error_code& ec);
	void start_write(const std::string & to_write);
	void handle_write(const boost::system::error_code& ec);

private:
	bool						ready;
	std::thread					service_thread;
	boost::asio::io_service		io_service;
	tcp::resolver				resolv;
	bool						stopped_;
	tcp::socket					socket_;
	boost::asio::streambuf		input_buffer_;
	LockedQueue<std::string>	incomingMessages;
};