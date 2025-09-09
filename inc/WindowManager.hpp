#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "Window.hpp"
#include "Text.hpp"
#include "Table.hpp"
#include "Button.hpp"
#include <string>
#include <vector>

using namespace std;

class WindowManager {
private:
	vector<WindowBase*> elements;
	Window* mainWindow = nullptr;
	WindowManager() {}
	WindowManager(const WindowManager&) = delete;
	WindowManager& operator = (const WindowManager&) = delete;
	WindowBase* findById(const string& id);
	bool isCellAvailable(Window* parent, int r, int c); 
public:
	static WindowManager& getInstance();
	~WindowManager();
	void addWindow(string id, int rows, int cols, string parentId="-1", int row=-1, int col=-1);
	void addText(string id, string text, string parentId, int row, int col);
	void addTable(string id, int rows, int cols, string parentId, int row, int col);
	void addButton(string id, string text, string parentId, int row, int col);
	void drawAll();	
};

#endif
