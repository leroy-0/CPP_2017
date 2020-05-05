#pragma once

#include "IConnection.h"
#include <memory>
#include <string>

class Factory
{
public:
	static std::unique_ptr<IConnection> CreateUdpClient(std::string host, unsigned int server_port, unsigned int client_port);
	static std::unique_ptr<IConnection> CreateTcpClient(std::string host, unsigned int server_port, unsigned int client_port);
};