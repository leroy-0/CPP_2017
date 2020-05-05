#pragma once

#include "Common.h"
#include "Sound.h"
#include "IConnection.h"
#include <sstream>
#include <memory>
#include <vector>
#include <map>

class ConnectInfo
{
public:
	ConnectInfo();
	virtual ~ConnectInfo();

	void							start();
	void							stop();
	void							checkStatus(const std::string & ip, const std::string & port);
	mod								run(const std::string & ip, const std::string & port);

	std::map<int, int>	&			getRoomIds();
	std::unique_ptr<IConnection> &	getUdp();
	std::unique_ptr<IConnection> &	getTcp();
	std::vector<std::string> &		getPlayerIds();
	std::string	&					getMyPlayerId();
	std::map<std::string, bool> &	isConnecting();

	template<typename Out>
	void split(const std::string &s, char delim, Out result);
	std::vector<std::string> split(const std::string &s, char delim);

private:
	mod								analyseRFC(const std::string & ip, const std::string & port);

private:
	std::map<std::string, bool>		isConnected;
	std::unique_ptr<IConnection>	tcpConnection;
	std::unique_ptr<IConnection>	udpConnection;
	std::map<int, int>				roomIds;
	std::vector<std::string>		playerIds;
	std::string						myplayerid;
};