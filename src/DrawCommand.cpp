#include "../inc/DrawCommand.hpp"
#include "../inc/WindowManager.hpp"

bool DrawCommand::validate(istringstream&)
{
       	return true; 
}
void DrawCommand::execute()
{ 
	WindowManager::getInstance().drawAll(); 
}
