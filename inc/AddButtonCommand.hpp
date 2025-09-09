#ifndef ADDBUTTONCOMMAND_HPP
#define ADDBUTTONCOMMAND_HPP

#include "Command.hpp"
#include <string>
using namespace std;

class AddButtonCommand : public Command {
private:
	string id, text, parentId;
	int r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override;
	void execute() override;
};

#endif
