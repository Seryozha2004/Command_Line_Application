#include "../inc/AddTableCommand.hpp"
#include "../inc/WindowManager.hpp"

bool AddTableCommand::validate(istringstream& iss)
{
	if(!(iss>>id>>rows>>cols>>parentId>>r>>c)) return false;
	valid = true;
	return true;
}
void AddTableCommand::execute()
{
	if(valid) WindowManager::getInstance().addTable(id, rows, cols, parentId, r, c);
}
