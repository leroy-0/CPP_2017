#include "ConnectInfo.h"
#include "Factory.h"
#include <iostream>
#include <string>

ConnectInfo::ConnectInfo()
{

}

ConnectInfo::~ConnectInfo()
{

}

template<typename Out>
void ConnectInfo::split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> ConnectInfo::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

void	ConnectInfo::stop()
{
	this->getPlayerIds().clear();
	this->getMyPlayerId().clear();
	this->getRoomIds().clear();
	this->getTcp().reset();
	this->getUdp().reset();
}

void	ConnectInfo::start()
{
	this->isConnected["connect"] = false;
	this->isConnected["sendConnect"] = false;
	this->isConnected["ready"] = false;
	this->isConnected["sendReady"] = false;
	this->isConnected["launch"] = false;
	this->isConnected["sendLaunch"] = false;
	this->isConnected["sendGo"] = false;
}

mod		ConnectInfo::analyseRFC(const std::string & ip, const std::string & port)
{
	std::vector<std::string>	words;
	std::vector<std::string>	words2;
	std::string					str;
	int							code;

	if (this->getTcp()->HasMessages())
	{
		str = this->getTcp()->GetOneMessage();
		std::cout << "Received Message: " <<  str << std::endl;
		words = this->split(this->split(str, '\n')[0], ' ');
		if (words.size() == 0)
			return (mod::connection);

		code = std::stoi(words[0]);
		if (words.size() > 1)
			words = this->split(words[1], ':');
		else
			words.clear();

		switch (code)
		{
		case 102:
			this->getMyPlayerId() = words[2];
			this->getTcp() = Factory::CreateTcpClient(ip, std::stoi(words[1]), 0);
			this->isConnecting()["launch"] = true;
			break;
		case 103:
			this->getUdp() = Factory::CreateUdpClient(ip, std::stoi(words[1]), 0);
			break;
		case 105:
			this->getPlayerIds().clear();
			for (short i = 0; i < words.size(); i++)
				this->getPlayerIds().push_back(words[i]);
			break;
		case 107:
			for (short i = 0; i < words.size(); i++)
			{
				words2 = this->split(words[i], ',');
				this->getRoomIds()[std::stoi(words2[0])] = std::stoi(words2[1]);
			}
			break;
		case 106:
			return (mod::multiplayer);
		default:
			break;
		}
	}
	return (mod::connection);
}

mod		ConnectInfo::run(const std::string & ip, const std::string & port)
{
	if (this->isConnecting()["connect"] && this->getTcp()->isReady() == true)
	{
		if (this->isConnecting()["sendConnect"] == false)
		{
			this->getTcp()->Send("101 Connect");
			this->isConnecting()["sendConnect"] = true;
		}
		else if (this->isConnecting()["ready"] == true && 
			this->isConnecting()["sendReady"] == false)
		{
			if (this->getRoomIds().size() == 0)
				this->getTcp()->Send("108 Ready");
			else
				this->getTcp()->Send("109 " + std::to_string(0));
			this->isConnecting()["sendReady"] = true;
		}
		else
		{
			if (this->isConnecting()["launch"] == true
				&& this->isConnecting()["sendLaunch"] == false)
			{
				this->getTcp()->Send("110 " + this->getMyPlayerId());
				this->isConnecting()["sendLaunch"] = true;
			}
			else if (this->isConnecting()["sendGo"] == true && 
				this->getUdp()->isReady() == true)
			{
				this->getTcp()->Send("111 Let's go !");
				this->isConnecting()["sendGo"] = false;
			}
		}
		return (analyseRFC(ip, port));
	}
	return (mod::connection);
}

void	ConnectInfo::checkStatus(const std::string & ip, const std::string & port)
{
	if (!this->isConnecting()["connect"])
	{
		//this->sounds["select"]->play();
		this->isConnecting()["connect"] = true;
		this->getTcp() = Factory::CreateTcpClient(ip, std::stoi(port), 0);
	}
	else if (!this->isConnecting()["ready"])
	{
		//this->sounds["select"]->play();
		this->isConnecting()["ready"] = true;
	}
	else if (this->isConnecting()["launch"])
	{
		//this->sounds["select"]->play();
		this->isConnecting()["sendGo"] = true;
	}
}

std::map<int, int> &	ConnectInfo::getRoomIds()
{
	return (this->roomIds);
}

std::map<std::string, bool> &	ConnectInfo::isConnecting()
{
	return (this->isConnected);
}

std::unique_ptr<IConnection> &	ConnectInfo::getUdp()
{
	return (this->udpConnection);
}

std::unique_ptr<IConnection> &	ConnectInfo::getTcp()
{
	return (this->tcpConnection);
}

std::vector<std::string> &	ConnectInfo::getPlayerIds()
{
	return (this->playerIds);
}

std::string	&	ConnectInfo::getMyPlayerId()
{
	return (this->myplayerid);
}