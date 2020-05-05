//#define _WIN32_WINNT 0x0501
#include <boost/bind.hpp>
#include "Network/AsioUdpConnection.hpp"

AsioUdpConnection::AsioUdpConnection(unsigned short local_port) :
	socket(io_service, udp::endpoint(udp::v4(), local_port)),
	service_thread(&AsioUdpConnection::run_service, this),
	nextClientID(0L)
{
    std::cout << "----> New UDP Server <---- " << local_port << std::endl;
};

AsioUdpConnection::~AsioUdpConnection()
{
	io_service.stop();
	service_thread.join();
}

bool					AsioUdpConnection::clientConnected()
{
	return (true);
}

void					AsioUdpConnection::start_receive()
{
	socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
		boost::bind(&AsioUdpConnection::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void					AsioUdpConnection::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		try {
			auto message = ClientMessage(std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred), getId(remote_endpoint));
			//std::cout << "New Udp Message : " << std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred) << std::endl;
			if (!message.first.empty())
				messageQueue.push(message);
		}
		catch (std::exception ex) {
			std::cout <<"handle_receive: Error parsing incoming message:" << ex.what() << std::endl;
		}
		catch (...) {
			std::cout <<"handle_receive: Unknown error while parsing incoming message" << std::endl;
		}
	}
	else
	{
		std::cout <<"handle_receive: error: " << std::endl;
	}
	start_receive();
}

void AsioUdpConnection::send(std::string message, udp::endpoint target_endpoint)
{
	socket.send_to(boost::asio::buffer(message), target_endpoint);
}

void AsioUdpConnection::run_service()
{
	start_receive();
	while (!io_service.stopped()) {
		try {
			std::cout << "Running Service" << std::endl;
			io_service.run();
		}
		catch (const std::exception& e) {
			std::cout <<"Server network exception: "<< e.what() << std::endl;
		}
		catch (...) {
			std::cout <<"Unknown exception in server network thread" << std::endl;
		}
	}
	std::cout <<"Server network thread stopped" << std::endl;
};

unsigned int AsioUdpConnection::getId(udp::endpoint endpoint)
{
	for (auto it = clients.begin(); it != clients.end(); ++it)
		if (it->second == endpoint)
			return (it->first);
	nextClientID++;
	clients.insert(Client(nextClientID, endpoint));
	return (nextClientID);
};

void AsioUdpConnection::sendMessage(std::string message, unsigned int clientID)
{
	try {
//        std::cout << "Message Send (UDP) " << message << std::endl;
		send(message, clients.at(clientID));
	}
	catch (std::out_of_range) {
		std::cout <<"Unknown client ID" << std::endl;
	}
};

void AsioUdpConnection::sendMessageAll(std::string message)
{
	for (auto it = clients.begin(); it != clients.end(); ++it)
		send(message, it->second);
};

ClientMessage AsioUdpConnection::getMessages() {
	return messageQueue.pop();
}

bool AsioUdpConnection::checkMessages()
{
	return !messageQueue.empty();
};

void AsioUdpConnection::wait() 
{
	std::cout << "Waiting" << std::endl;
	service_thread.join();
	std::cout << "Thread finished" << std::endl;
}

std::unique_ptr<AsioUdpConnection>	AsioUdpConnection::createConnection(unsigned int port)
{
	auto server = new AsioUdpConnection(port);
	return std::unique_ptr<AsioUdpConnection>(server);
}