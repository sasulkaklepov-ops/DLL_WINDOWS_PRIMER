#include <Windows.h>
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	DWORD pid;

	cout << "Write PID process: ";
	cin >> pid;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (!hProcess) {
		cout << "Error OpenProcess: " << GetLastError << endl;

		return 1;
	}

	const char* dllPath = "C:\\temp\\mydll.dll";

	LPVOID mem = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE , PAGE_READWRITE);

	WriteProcessMemory(hProcess, mem, dllPath, strlen(dllPath) + 1, NULL);

	LPVOID loadLib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLib, mem, 0, NULL);

	cout << "Great! Check notepad." << endl;

    CloseHandle(hProcess);

	return 0;
}
