#pragma once
#include <string>

typedef std::pair<std::string, unsigned int>			ClientMessage;

class IConnection {
	public:
		virtual	~IConnection() {};
		virtual bool			clientConnected() = 0;
		virtual bool			checkMessages() = 0;
		virtual ClientMessage	getMessages() = 0;
		virtual void			sendMessage(std::string message, unsigned int clientID) = 0;
		virtual void			sendMessageAll(std::string message) = 0;
};