#include "../inc/WindowManager.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
	WindowManager wm;
	string line;
	while(true)
	{
		cout<<"> ";
		if(!getline(cin, line)) break;
		if(line == "quit") break;
		istringstream iss(line);
		string cmd;
		iss>>cmd;
		if(cmd == "add_window")
		{
			string id;
			int rows, cols;
			if(!(iss>>id>>rows>>cols))
			{
				cerr<<"Usage: add_window <id> <rowCount> <colCount> [parentWindowId=-1] [row=-1] [col=-1]\n";
				continue;
			}
			string parentId="-1";
			int r=-1, c=-1;
			iss>>parentId>>r>>c;
			wm.addWindow(id, rows, cols, parentId, r, c);
		}
		else if(cmd == "add_text")
		{
			string id, text, parentId;
			int r, c;
			if(!(iss>>id>>text>>parentId>>r>>c))
			{
				cerr<<"Usage: add_text <id> <text> <parentWindowId> <row> <col>\n";
				continue;
			}
			wm.addText(id, text, parentId, r, c);
		}
		else if(cmd == "add_table")
		{
			string id, parentId;
			int rows, cols, r, c;
			if(!(iss>>id>>rows>>cols>>parentId>>r>>c))
			{
				cerr<<"Usage: add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>\n";
				continue;
			}
			wm.addTable(id, rows, cols, parentId, r, c);
		}
		else if(cmd == "add_button")
		{
			string id, text, parentId;
			int r, c;
			if(!(iss>>id>>text>>parentId>>r>>c))
			{
				cerr<<"Usage: add_button <id> <text> <parentWindowId> <row> <col>\n";
				continue;
			}
			wm.addButton(id, text, parentId, r, c);
		}
		else if(cmd == "draw")
		{
			wm.drawAll();
		}
		else cerr<<"Unknown command!\n";
	}
	return 0;
}
