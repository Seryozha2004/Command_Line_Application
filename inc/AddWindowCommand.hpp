#ifndef ADDWINDOWCOMMAND_HPP
#define ADDWINDOWCOMMAND_HPP

#include "Command.hpp"
#include <string>
using namespace std;

class AddWindowCommand : public Command {
private:
	string id, parentId;
	int rows, cols, r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override;
	void execute() override;
};

#endif
