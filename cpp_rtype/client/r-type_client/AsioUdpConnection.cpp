#pragma once

#include <iostream>
#include <fstream>
#include "AsioUdpConnection.h"

AsioUdpConnection::AsioUdpConnection(const std::string & host, unsigned short server_port, unsigned short local_port) :
	socket(io_service, udp::endpoint(udp::v4(), local_port)),
	service_thread(&AsioUdpConnection::run_service, this)
{
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), host, std::to_string(server_port));
	server_endpoint = *resolver.resolve(query);
	this->ready = true;
}

AsioUdpConnection::~AsioUdpConnection()
{
	io_service.stop();
	service_thread.join();
}

void AsioUdpConnection::start_receive()
{
	socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
		[this](std::error_code ec, std::size_t bytes_recvd) { 
		this->handle_receive(ec, bytes_recvd); });
}

void AsioUdpConnection::handle_receive(const std::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		std::string message(recv_buffer.data(), recv_buffer.data() + bytes_transferred);
		incomingMessages.push(message);
	}
	else
	{
		std::cout << "Client::handle_receive:," << error  << std::endl;
	}
	start_receive();
}

void AsioUdpConnection::Send(const std::string& message)
{
	/*std::string secure_message;

	secure_message = secure_code;
	secure_message += " ";
	std::chrono::seconds s = std::chrono::duration_cast< std::chrono::seconds >(
		std::chrono::system_clock::now().time_since_epoch()
		);
	secure_message += std::to_string(s.count());
	secure_message += " ";
	secure_message += message;*/
	socket.send_to(boost::asio::buffer(message), server_endpoint);
}

bool AsioUdpConnection::HasMessages()
{
	return !incomingMessages.empty();
}

std::string AsioUdpConnection::GetOneMessage()
{
	if (incomingMessages.empty())
		return (std::string());
	return incomingMessages.pop();
}

bool		AsioUdpConnection::isReady() const
{
	return (this->ready);
}

void AsioUdpConnection::run_service()
{
	start_receive();
	while (!io_service.stopped()) {
		try {
			io_service.run();
		}
		catch (const std::exception& e) {
			std::cout << "Client: network exception: ," << e.what() << std::endl;

		}
		catch (...) {
			std::cout << "Unknown exception in client network thread" << std::endl;
		}
	}
}