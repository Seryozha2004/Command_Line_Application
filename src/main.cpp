#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../inc/CommandFactory.hpp"
using namespace std;

int main()
{
	string line;
	while(true)
	{
		cout<<"> ";
		if(!getline(cin, line)) break;
		if(line == "quit") break;
		istringstream iss(line);
		string cmdName;
		iss>>cmdName;
		Command* cmd = CommandFactory::createCommand(cmdName);
		if(!cmd)
		{
			cerr<<"Unknown command!\n";
			continue;
		}
		if(!cmd->validate(iss))
		{
			cerr<<"Invalid arguments for command: "<<cmdName<<endl;
			delete cmd;
			continue;
		}
		cmd->execute();
		delete cmd;
	}
	return 0;
}
