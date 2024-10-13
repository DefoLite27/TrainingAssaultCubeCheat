#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>


class Memory
{
private:
	uintptr_t id = 0; // Process ID
    HANDLE process = NULL;
	uintptr_t GetProcess(const wchar_t* procName) {
		HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32W processEntry = { };
		processEntry.dwSize = sizeof(PROCESSENTRY32W);

		if (Process32FirstW(snapshotHandle, &processEntry)) {
			do {
				if (_wcsicmp(processEntry.szExeFile, procName) == 0) {
					CloseHandle(snapshotHandle);
					return processEntry.th32ProcessID;
				}
			} while (Process32NextW(snapshotHandle, &processEntry));
		}

		CloseHandle(snapshotHandle);
		return NULL;
	}

public:

	uintptr_t baseAdrs = NULL;

	Memory(const wchar_t* procName, const wchar_t* ModuleTarget) {
		this->id = GetProcess(procName);
		this->process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->id);
		
		HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->id);

		MODULEENTRY32W moduleEntry = { };
		moduleEntry.dwSize = sizeof(MODULEENTRY32W);

		//std::wcout << L"TargetModule Name: " << ModuleTarget << std::endl;

		if (Module32FirstW(snapshotHandle, &moduleEntry)) {
			do {
				//std::wcout << L"Module Name: " << moduleEntry.szModule << std::endl;
				if (_wcsicmp(moduleEntry.szModule, ModuleTarget) == 0) {
					CloseHandle(snapshotHandle);
					baseAdrs = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
				}
			} while (Module32NextW(snapshotHandle, &moduleEntry));
		}

		//CloseHandle(snapshotHandle);
	}

	// Getters
	uintptr_t GetProcId() { return this->id; }
	uintptr_t GetBaseAdrs() { return this->baseAdrs; }
	///

	// Functions
	template <typename t>
	auto ReadRaw(int offSet) {
		t value = { };
		ReadProcessMemory(this->process, (LPVOID)(offSet), &value, sizeof(t), NULL);
		return value;
	}
	template <typename t>
	auto Read(int offSet){
		return ReadRaw<t>(this->baseAdrs + offSet);
	}

	template <typename t>
	bool Write(int offSet, t value) {
		return WriteProcessMemory(this->process, (LPVOID)(this->baseAdrs + offSet), &value, sizeof(t), NULL);
	}
	///

};