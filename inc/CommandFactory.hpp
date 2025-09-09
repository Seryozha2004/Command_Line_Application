#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Command.hpp"
#include <string>
using namespace std;

class CommandFactory {
public:
	static Command* createCommand(const string& cmdName);
};

#endif
