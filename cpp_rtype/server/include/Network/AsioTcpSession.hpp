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
#include	"Network/IConnection.hpp"
#include	"Network/locked_queue.hpp"
#define		B_SIZE 4096

using boost::asio::ip::tcp;

class AsioTcpSession : public std::enable_shared_from_this<AsioTcpSession>
{
public:
	typedef std::shared_ptr<AsioTcpSession>	pointer;
	static pointer							create(boost::asio::io_service& io_service);
	void									sendMessage(const std::string & message);
	bool									hasMessages();
	std::string								getMessage();
	void									start();
	tcp::socket	&							getSocket();
	bool									isConnected();
	virtual ~AsioTcpSession();

private:
	AsioTcpSession(boost::asio::io_service& io_service);
	void									start_write(const std::string & message);
	void									start_read();
	void									handle_write(const boost::system::error_code &error, size_t bytes_transferred);
	void									handle_read(const boost::system::error_code& error, size_t bytes_transferred);

private:
	bool									connected;
	tcp::socket								socket;
	std::queue<std::string>					received;
	std::array<char, B_SIZE>				recv_buffer;
};

