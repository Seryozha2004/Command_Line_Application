#ifndef ADDTABLECOMMAND_HPP
#define ADDTABLECOMMAND_HPP

#include "Command.hpp"
#include <string>

class AddTableCommand : public Command {
private:
	string id, parentId;
	int rows, cols, r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override;
	void execute() override;
};

#endif
