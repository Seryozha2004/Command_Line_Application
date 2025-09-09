#ifndef DRAWCOMMAND_HPP
#define DRAWCOMMAND_HPP

#include "Command.hpp"

class DrawCommand : public Command {
public:
	bool validate(istringstream&) override;
	void execute() override;
};

#endif
