#include "Network/AsioTcpConnection.hpp"
#include "Network/ConnectionCreate.hpp"

std::unique_ptr<IConnection>	ConnectionCreate::createUdpConnection(unsigned int port)
{
	auto server = new AsioUdpConnection(port);
	return std::unique_ptr<IConnection>(server);
}

std::unique_ptr<IConnection> ConnectionCreate::createTcpConnection(unsigned int port) {
	auto server = new AsioTcpConnection(port);
	return std::unique_ptr<IConnection>(server);
}
