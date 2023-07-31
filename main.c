#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>

#define MAX_PATH 260
#define BUFFER_SIZE 1024

HANDLE create_mutex(const char *name)
{
	HANDLE mutex = CreateMutex(NULL, FALSE, name);
	if (mutex == NULL)
	{
		fprintf(stderr, "Failed to create mutex: %d\n", GetLastError());
		exit(EXIT_FAILURE);
	}
	return mutex;
}

BOOL is_process_running(const char *process_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &entry))
	{
		do
		{
			if (_stricmp(entry.szExeFile, process_name) == 0)
			{
				CloseHandle(snapshot);
				return TRUE;
			}
		} while (Process32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
	return FALSE;
}

void run_game(const char *path)
{
	char exe_path[BUFFER_SIZE];
	char steam_api_path[BUFFER_SIZE];
	char ul_steam_api_path[BUFFER_SIZE];
	char exe_path_quoted[BUFFER_SIZE];

	sprintf(exe_path, "%s/TestDrive2.exe", path);
	sprintf(steam_api_path, "%s/steam_api.dll", path);
	sprintf(ul_steam_api_path, "%s/UL_steam_api.dll", path);
	sprintf(exe_path_quoted, "\"%s\"", exe_path);

	if (_access(exe_path, 0) != -1)
	{
		if (_access(steam_api_path, 0) != -1)
		{
			rename(steam_api_path, ul_steam_api_path);
		}

		_chdir(path);
		system(exe_path_quoted);

		if (_access(ul_steam_api_path, 0) != -1)
		{
			rename(ul_steam_api_path, steam_api_path);
		}
	}
	else
	{
		fprintf(stderr, "Path %s does not exist!\n", path);
	}
}

void run_game_with_mutex(const char *hash, const char *path)
{
	if (is_process_running("TestDrive2.exe"))
	{
		fprintf(stderr, "Game is already running!\n");
		return;
	}

	HANDLE mutex = create_mutex(hash);
	run_game(path);
	WaitForSingleObject(mutex, INFINITE);
	ReleaseMutex(mutex);
}

void read_config(char *path)
{
	FILE *fp = fopen("path.txt", "r");
	if (fp == NULL)
	{
		perror("Could not open path.txt");
		exit(EXIT_FAILURE);
	}

	fgets(path, BUFFER_SIZE, fp);
	path[strcspn(path, "\n")] = 0;

	fclose(fp);
}

int main()
{
	char path[BUFFER_SIZE];
	read_config(path);

	run_game_with_mutex("wont_leak_da_hash", path);

	return 0;
}
