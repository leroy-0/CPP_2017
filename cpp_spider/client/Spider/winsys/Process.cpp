#include "stdafx.h"
#include <Windows.h>

#include <psapi.h>
#include <atlstr.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

#include "Process.h"

Process::Process()
{
	lastProcId = this->getProcessIdByWindowName(this->getActiveWindowTitle());
}

Process::~Process()
{

}

bool				Process::isModified()
{
	unsigned int	procId;

	procId = this->getProcessIdByWindowName(this->getActiveWindowTitle());
	if (procId != 0 && lastProcId != procId)
	{
		lastProcId = procId;
		return (true);
	}
	return (false);
}

void		Process::hideWindow() const
{
	HWND	Stealth;
	
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

const std::string 	Process::getProcessPath(unsigned int pid) const
{
	PROCESSENTRY32	peInfo;
	HANDLE			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
	BOOL			nextProcess;
	std::string		path;
	bool			found;

	if (hSnapshot)
	{
		peInfo.dwSize = sizeof(peInfo);
		nextProcess = Process32First(hSnapshot, &peInfo);
		found = false;
		while (nextProcess)
		{
			if (peInfo.th32ProcessID == pid)
			{
				found = true;
				break;
			}
			nextProcess = Process32Next(hSnapshot, &peInfo);
		}
		if (found)
		{
			path = std::string(peInfo.szExeFile);
		}
		CloseHandle(hSnapshot);
	}
	return (path);
}

const std::string 	Process::getActiveWindowTitle() const
{
	char			wnd_title[256];
	HWND			hwnd = GetForegroundWindow();
	
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return (wnd_title);
}

unsigned int		Process::getProcessIdByProcessName(const std::string & processName) const
{
	PROCESSENTRY32	peInfo;
	HANDLE			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	BOOL			nextProcess;

	if (hSnapshot)
	{
		peInfo.dwSize = sizeof(peInfo);
		nextProcess = Process32First(hSnapshot, &peInfo);
		while (nextProcess)
		{
			if (peInfo.szExeFile == processName)
			{
				CloseHandle(hSnapshot);
				return (peInfo.th32ProcessID);
			}
			nextProcess = Process32Next(hSnapshot, &peInfo);
		}
		CloseHandle(hSnapshot);
	}
	return (0);
}

unsigned int		Process::getProcessIdByWindowName(const std::string & winTitle) const
{
	DWORD			pid;
	LPCSTR			name = winTitle.c_str();
	HWND			windowHandle = FindWindow(NULL, name);
	unsigned int	val;

	val = GetWindowThreadProcessId(windowHandle, &pid);
	if (val == 0)
		pid = GetCurrentProcessId();
	return (pid);
}