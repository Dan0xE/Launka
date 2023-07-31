#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#define MAX_PATH 260

#define BUFFER_SIZE 1024

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

void run_game(char *path)
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

int main()
{
	char path[BUFFER_SIZE];

	read_config(path);
	run_game(path);

	return 0;
}
