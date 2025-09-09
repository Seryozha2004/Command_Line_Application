#include "../inc/CommandFactory.hpp"
#include "../inc/AddWindowCommand.hpp"
#include "../inc/AddTextCommand.hpp"
#include "../inc/AddTableCommand.hpp"
#include "../inc/AddButtonCommand.hpp"
#include "../inc/DrawCommand.hpp"

Command* CommandFactory::createCommand(const string& cmdName)
{
	if(cmdName == "add_window") return new AddWindowCommand();
	else if(cmdName == "add_text") return new AddTextCommand();
	else if(cmdName == "add_table") return new AddTableCommand();
	else if(cmdName == "add_button") return new AddButtonCommand();
	else if(cmdName == "draw") return new DrawCommand();
	return nullptr;
}
