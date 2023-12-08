#include "overlay.h"
#include <ctime>
#include "xorstr.h"
#include <iostream>

#include <WinInet.h>
#include <urlmon.h>
#include <random>

#pragma comment(lib, "WinInet.lib")
#pragma comment(lib, "urlmon.lib") 

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
	{
		ov::clean_directx();
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

std::string RandomStrings(int len)
{
	srand(time(NULL));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

bool RenameFile(std::string& path)
{
	std::string newPath = (RandomStrings(16) + ".exe");
	if (std::rename(path.c_str(), newPath.c_str()))
		return false;
	path = newPath;
	return true;
}


int main(int argCount, char** argVector)
{
	std::string filePath = argVector[0];

	if (!RenameFile(filePath))
	{
		return -1;
	}

	SetConsoleTitleA(RandomStrings(16).c_str());

	init();
	ov::create_window();

	ov::loop();
}