#include <ctime>
#include "Network/AsioTcpConnection.hpp"

AsioTcpConnection::AsioTcpConnection(unsigned short port)
	:  
	acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
	service_thread(&AsioTcpConnection::run_service, this),
	nextClientID(0L)
{
	boost::asio::ip::tcp::acceptor::reuse_address option(true);
	acceptor.set_option(option);
	std::cout << "----> New TCP Server <---- " << port << std::endl;
}

AsioTcpConnection::~AsioTcpConnection()
{
	acceptor.close();
	io_service.stop();
}

bool							AsioTcpConnection::clientConnected()
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[0]->isConnected())
			return (true);
	}
	return (false);
}

bool							AsioTcpConnection::checkMessages()
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->hasMessages())
			return (true);
	}
	if (messages.empty())
		return (false);
	return (true);
}

ClientMessage					AsioTcpConnection::getMessages()
{
	ClientMessage				tmp;

	for (int i = 0; i < clients.size(); i++)
	{
		while (clients[i]->hasMessages())
			messages.push(ClientMessage(clients[i]->getMessage(), i));
	}
	tmp = ClientMessage(messages.front());
	messages.pop();
	return (tmp);
}

void							AsioTcpConnection::sendMessage(std::string message, unsigned int clientID)
{
    std::cout << "Message Send (TCP) " << message << std::endl;
    for (int i = 0; i < clients.size(); i++)
	{
		if (clientID == i)
		{
			clients[i]->sendMessage(message);
			return;
		}
	}
	std::cout << "Invalid client number" << std::endl;
}

void							AsioTcpConnection::sendMessageAll(std::string message)
{
	for (int i = 0; i < clients.size(); i++)
	{
		clients[i]->sendMessage(message);
	}
}

void							AsioTcpConnection::start_accept()
{
	AsioTcpSession::pointer		new_connection = AsioTcpSession::create(acceptor.get_io_service());

	clients.insert(ClientTcp(nextClientID, new_connection));
	nextClientID++;
	acceptor.async_accept(new_connection->getSocket(),
		boost::bind(&AsioTcpConnection::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
}

void							AsioTcpConnection::handle_accept(AsioTcpSession::pointer new_connection, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "New client" << std::endl;
		new_connection->start();
	}
	start_accept();
}

void							AsioTcpConnection::run_service()
{
	try
	{
		start_accept();
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void							AsioTcpConnection::wait()
{
	std::cout << "Waiting" << std::endl;
	service_thread.join();
	std::cout << "Thread finished" << std::endl;
}
