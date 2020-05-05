#pragma once

#include <string>

class Process
{
public:
	Process();
	virtual ~Process();

public:
	const std::string 		getActiveWindowTitle() const;
	const std::string 		getProcessPath(unsigned int pid) const;
	unsigned int			getProcessIdByProcessName(const std::string & processName) const;
	unsigned int			getProcessIdByWindowName(const std::string & processName) const;
	void					hideWindow() const;
	bool					isModified();

private:
	unsigned int			lastProcId;
};