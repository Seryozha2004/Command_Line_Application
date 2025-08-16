#include "../inc/WindowManager.hpp"
#include <iostream>
using namespace std;

WindowBase* WindowManager::findById(const string& id)
{
	for(WindowBase* e : elements)
	{
		if(e->getId() == id) return e;
	}
	return nullptr;
}
bool WindowManager::isCellAvailable(Window* parent, int r, int c)
{
	if(!parent)
	{
		cerr<<"Parent window is null!\n";
		return false;
	}
	if(r<0 || c<0 || r>=parent->getRowCount() || c>=parent->getColCount())
	{
		cerr<<"Cell ("<<r<<","<<c<<") is out of window "<<parent->getId()<<"!\n";
		return false;
	}
	for(WindowBase* child : parent->getChildren())
	{
		if(child->getRow() == r && child->getCol() == c)
		{
			cerr<<"Cell ("<<r<<","<<c<<") is already occupied by Id: "<<child->getId()<<endl;
			return false;
		}
	}
	return true;
}

WindowManager::~WindowManager()
{
	for(WindowBase* e : elements) delete e;
}
void WindowManager::addWindow(string id, int rows, int cols, string parentId, int row, int col)
{
	if(findById(id) != nullptr)
	{
		cerr<<"Element with ID "<<id<<" already exists!\n";
		return;
	}
	if(parentId == "-1")
	{
		if(mainWindow != nullptr)
		{
			cerr<<"Main window already exists!\n";
			return;
		}
		mainWindow = new Window(id, rows, cols, nullptr, row, col);
		elements.push_back(mainWindow);
		return;
	}
	WindowBase* parent = findById(parentId);
	if(!parent)
	{
		cerr<<"Parent window not found!\n";
		return;
	}
	Window* pw = dynamic_cast<Window*>(parent);
	if(!pw)
	{
		cerr<<"Parent is not a window!\n";
		return;
	}
	if(!isCellAvailable(pw, row, col)) return;
	Window* win = new Window(id, rows, cols, parent, row, col);
	elements.push_back(win);
	pw->addChild(win);
}
void WindowManager::addText(string id, string text, string parentId, int row, int col)
{
	if(findById(id) != nullptr)
	{
		cerr<<"Element with ID "<<id<<"already exists!\n";
		return;
	}
	WindowBase* parent = findById(parentId);
	if(!parent)
	{
		cerr<<"Parent window not found!\n";
		return;
	}
	Window* pw = dynamic_cast<Window*>(parent);
	if(!pw)
	{
		cout<<"Parent is not a window!\n";
		return;
	}
	if(!isCellAvailable(pw, row, col)) return;
	Text* t = new Text(id, text, parent, row, col);
	elements.push_back(t);
	pw->addChild(t);
}
void WindowManager::addTable(string id, int rows, int cols, string parentId, int row, int col)
{
	if(findById(id) != nullptr)
	{
		cerr<<"Element with ID "<<id<<"already exists!\n";
		return;
	}
	WindowBase* parent = findById(parentId);
	if(!parent)
	{
		cerr<<"Parent window not found!\n";
		return;
	}
	Window* pw = dynamic_cast<Window*>(parent);
	if(!pw)
	{
		cerr<<"Parent is not a window!\n";
		return;
	}
	if(!isCellAvailable(pw, row, col)) return;
	Table* tbl = new Table(id, rows, cols, parent, row, col);
	elements.push_back(tbl);
	pw->addChild(tbl);
}
void WindowManager::addButton(string id, string text, string parentId, int row, int col)
{
	if(findById(id) != nullptr)
	{
		cerr<<"Element with ID "<<id<<"already exists!\n";
		return;
	}
	WindowBase* parent = findById(parentId);
	if(!parent)
	{
		cerr<<"Parent window not found!\n";
		return;
	}
	Window* pw = dynamic_cast<Window*>(parent);
	if(!pw)
	{
		cerr<<"Parent is not a window!\n";
		return;
	}
	if(!isCellAvailable(pw, row, col)) return;
	Button* btn = new Button(id, text, parent, row, col);
	elements.push_back(btn);
	pw->addChild(btn);
}
void WindowManager::drawAll()
{
	if(mainWindow) mainWindow->draw();
	else cerr<<"No main window to draw!\n";
}
