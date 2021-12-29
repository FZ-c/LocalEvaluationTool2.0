#include <iostream>

#include "Core/CommandManager/command.h"

using namespace std;

void windowSet()
{
	//设置窗口大小
	system("mode con cols=130 lines=30");
	//禁用最大化按钮
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	DestroyMenu(hMenu);
	ReleaseDC(hWnd, NULL);
}

int main()
{
	windowSet();
	std::string cmd;
	while(1)
	{
		std::cout << CCommand::instance()->getExePath() << ">";
		getline(cin, cmd);
		if (cmd == "exit") break;
		CCommand::instance()->runCommand(cmd);
	}
	return 0;
}
