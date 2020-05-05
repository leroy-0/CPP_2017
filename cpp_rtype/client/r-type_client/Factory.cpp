#include "Factory.h"
#include "AsioUdpConnection.h"
#include "AsioTcpConnection.h"

std::unique_ptr<IConnection> Factory::CreateUdpClient(std::string host, unsigned int server_port, unsigned int client_port)
{
	auto client = new AsioUdpConnection(host, server_port, client_port);
	return std::unique_ptr<IConnection>(client);
}

std::unique_ptr<IConnection> Factory::CreateTcpClient(std::string host, unsigned int server_port, unsigned int client_port)
{
	auto client = new AsioTcpConnection(host, std::to_string(server_port));
	return std::unique_ptr<IConnection>(client);
}
