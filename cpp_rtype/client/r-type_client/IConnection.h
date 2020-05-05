#pragma once

#include <string>

class IConnection abstract
{
public:
	virtual ~IConnection() {};
	virtual bool HasMessages() abstract = 0;
	virtual void Send(const std::string& message) abstract = 0;
	virtual std::string GetOneMessage() abstract = 0;
	virtual bool isReady() const abstract = 0;
};