#pragma once

#include "KeyLogger.h"
#include "Comunication.h"
#include "TaskManager.h"

class IClient
{
public:
	virtual ~IClient() {};
	virtual bool	run() = 0;
};