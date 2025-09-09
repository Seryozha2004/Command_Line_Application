#include "../inc/AddTextCommand.hpp"
#include "../inc/WindowManager.hpp"

bool AddTextCommand::validate(istringstream& iss) 
{
	if(!(iss>>id>>text>>parentId>>r>>c)) return false;
	valid = true;
	return true;
}
void AddTextCommand::execute()
{
	if(valid) WindowManager::getInstance().addText(id, text, parentId, r, c);
}

