#include "../inc/AddWindowCommand.hpp"
#include "../inc/WindowManager.hpp"

bool AddWindowCommand::validate(istringstream& iss)
{
	if(!(iss>>id>>rows>>cols)) return false;
	parentId="-1"; 
	r=-1; 
	c=-1;
	iss>>parentId>>r>>c;
	valid = true;
	return true;
}
void AddWindowCommand::execute()
{
	if(valid) WindowManager::getInstance().addWindow(id, rows, cols, parentId, r, c);
}

