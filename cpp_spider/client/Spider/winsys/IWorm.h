#pragma once

class IWorm
{
public:
	virtual ~IWorm() {};
	virtual bool	run() = 0;
};