#include <iostream>

#include "Core/CommandManager/command.h"

using namespace std;

int main()
{
	std::string cmd;
	while (1)
	{
		std::cout << CCommand::instance()->getExePath() << ">";
		getline(cin, cmd);
		if (cmd == "exit") break;
		CCommand::instance()->runCommand(cmd);
	}
	return 0;
}
