#include "../inc/AddButtonCommand.hpp"
#include "../inc/WindowManager.hpp"

bool AddButtonCommand::validate(istringstream& iss)
{
	if(!(iss>>id>>text>>parentId>>r>>c)) return false;
	valid = true;
	return true;
}
void AddButtonCommand::execute()
{
	if(valid) WindowManager::getInstance().addButton(id, text, parentId, r, c);
}
