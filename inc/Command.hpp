#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <sstream>
using namespace std;

class Command {
public:
	virtual ~Command() {}
	virtual bool validate(istringstream& iss) = 0;
	virtual void execute() = 0;
};

#endif
