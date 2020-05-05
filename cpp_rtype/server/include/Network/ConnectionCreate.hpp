#pragma once
#include "Network/AsioUdpConnection.hpp"
#include "Network/AsioTcpConnection.hpp"

class ConnectionCreate {
public:
	static std::unique_ptr<IConnection> createUdpConnection(unsigned int port);
	static std::unique_ptr<IConnection> createTcpConnection(unsigned int port);
};