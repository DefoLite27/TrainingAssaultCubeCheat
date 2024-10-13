#pragma once
#include <windows.h>
#include <iostream>

class WinFunc
{

public:

	DWORD processID;
	HANDLE processHandle;
	//static HWND windowHandle;

	static DWORD GetPID(LPCSTR process_name) {
		DWORD processID;
		HWND windowHandle = FindWindowA(nullptr, process_name);
		GetWindowThreadProcessId(windowHandle, &processID);

		return processID;
	}

	static HANDLE GetHandle(DWORD pid)
	{
		return OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, false, pid);
	}

	void GetInfo(LPCSTR process_name)
	{
		processID = GetPID(process_name);
		processHandle = GetHandle(processID);
	}
	void Print()
	{
		std::cout << "=============================" << "\n";
		std::cout << "=========== Game ============" << "\n";
		std::cout << "=============================" << "\n\n";

		std::cout << "PID:    " << processID << "\n";
		std::cout << "Handle: " << processHandle << "\n";

		std::cout << "\n\n";
	}

	template <class T>
	T Read(LPCVOID address)
	{
		T VALUE;
		ReadProcessMemory(processHandle, (LPCVOID)(address), &VALUE, sizeof(T), 0);
		return VALUE;
	}
};