#include "Network/AsioTcpSession.hpp"


AsioTcpSession::AsioTcpSession(boost::asio::io_service& io_service)
	: socket(io_service), connected(false)
{
	std::cout << "TCPS : CONSTRUCT" << std::endl;
}

AsioTcpSession::~AsioTcpSession()
{
	std::cout << "TCPS : DESTROY" << std::endl;
	boost::system::error_code	ec;

	socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
	if (ec)
		std::cout << "Socket didn't properly shutdown" << std::endl;
	socket.close();
}

tcp::socket &					AsioTcpSession::getSocket()
{
	std::cout << "TCPS : GETSOCKET" << std::endl;
	return (socket);
}

AsioTcpSession::pointer			AsioTcpSession::create(boost::asio::io_service& io_service)
{
	std::cout << "TCPS : CREATE" << std::endl;
	return (pointer(new AsioTcpSession(io_service)));
}

bool							AsioTcpSession::isConnected()
{
	return (connected);
}

void							AsioTcpSession::sendMessage(const std::string & message)
{
	std::cout << "TCPS : SENDMESSAGE" << std::endl;
	if (connected == true)
		start_write(message);
}

bool							AsioTcpSession::hasMessages()
{
	return (!received.empty());
}

std::string						AsioTcpSession::getMessage() {
	std::string					tmp;

	std::cout << "TCPS : GETMESSAGE" << std::endl;
	tmp = received.front();
	received.pop();
	return (tmp);
}

void							AsioTcpSession::start()
{
	std::cout << "TCPS : START" << std::endl;
	connected = true;
	start_read();
}

void							AsioTcpSession::start_write(const std::string & message)
{
	std::string					*test = new std::string(message);

	boost::asio::async_write(socket, boost::asio::buffer(*test),
		boost::bind(&AsioTcpSession::handle_write, shared_from_this(), boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void							AsioTcpSession::handle_write(const boost::system::error_code &error, size_t bytes_transferred)
{
	if (error && error != boost::asio::error::eof) {
		std::cout << "Error: " << error.message() << "\n";
		return;
	}
	if ((boost::asio::error::eof == error) ||
		(boost::asio::error::connection_reset == error))
	{
		std::cout << "Client disconnected" << std::endl;
		connected = false;
		//delete this;
	}
}

void							AsioTcpSession::start_read()
{
	boost::asio::async_read(socket, boost::asio::buffer(recv_buffer),
		boost::asio::transfer_at_least(1),
		boost::bind(&AsioTcpSession::handle_read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void							AsioTcpSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error && error != boost::asio::error::eof) {
		std::cout << "Error: " << error.message() << "\n";
		return;
	}
	if ((boost::asio::error::eof == error) ||
		(boost::asio::error::connection_reset == error))
	{
		connected = false;
		std::cout << "Client disconnecting" << std::endl;
		return;
	}
	received.push(std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred));
	std::cout << "New Tcp Message : " << std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred) << std::endl;
	start_read();
}