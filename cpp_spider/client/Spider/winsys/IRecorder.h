#pragma once

#include <iostream>

class IRecorder
{
public:
	virtual ~IRecorder() {};
	virtual void	write(const std::string & filename) = 0;
	virtual void	read() = 0;
};