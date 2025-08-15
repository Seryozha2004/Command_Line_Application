#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class WindowBase {
protected:
	string id;
	int row, col;
	WindowBase* parent;

public:
	WindowBase(string id, int row, int col, WindowBase* parent = nullptr)
		: id(id), row(row), col(col), parent(parent) {}
	virtual ~WindowBase() {}
	string getId() const { return id; }
	WindowBase* getParent() const { return parent; }
	int getRow() const { return row; }
	int getCol() const { return col; }
	virtual void draw(int indent = 0) const = 0;
};

class Window : public WindowBase {
private:
	int rowCount, colCount;
	vector<WindowBase*> children;

public:
	Window(string id, int rowCount, int colCount, WindowBase* parent=nullptr, int row=-1, int col=-1)
		: WindowBase(id, row, col, parent), rowCount(rowCount), colCount(colCount) {}
	void addChild(WindowBase* child)
	{
		children.push_back(child);
	}
	int getRowCount() const { return rowCount; }
	int getColCount() const { return colCount; }
	const vector<WindowBase*>& getChildren() const { return children; }
	void draw(int indent = 0) const override 
	{
		cout<<string(indent, ' ')<<"[Window] ID: "<<id
			<<" Size: "<<rowCount<<"x"<<colCount
			<<" Pos: ("<<row<<","<<col<<")\n";
		for(WindowBase* ch : children)
		{
			ch->draw(indent+2);
		}
	}
};

class Text : public WindowBase {
private:
	string text;
public:
	Text(string id, string text, WindowBase* parent, int row, int col)
		: WindowBase(id, row, col, parent), text(text) {}
	void draw(int indent = 0) const override
	{
		cout<<string(indent, ' ')<<"[Text] ID: "<<id
			<<" \""<<text<<"\" Pos: ("<<row<<","<<col<<")\n";
	}
};

class Table : public WindowBase {
private:
	int rowCount, colCount;
public:
	Table(string id, int rowCount, int colCount, WindowBase* parent, int row, int col)
		: WindowBase(id, row, col, parent), rowCount(rowCount), colCount(colCount) {}
	void draw(int indent = 0) const override
	{
		cout<<string(indent, ' ')<<"[Table] ID: "<<id
			<<" Size: "<<rowCount<<"x"<<colCount
			<<" Pos: ("<<row<<","<<col<<")\n";
	}
};

class Button : public WindowBase {
private:
	string text;
public:
	Button(string id, string text, WindowBase* parent, int row, int col)
		: WindowBase(id, row, col, parent), text(text) {}
	void draw(int indent = 0) const override
	{
		cout<<string(indent, ' ')<<"[Button] ID: "<<id
			<<" \""<<text<<"\" Pos: ("<<row<<","<<col<<")\n";
	}
};

class WindowManager {
private:
	vector<WindowBase*> elements;
	Window* mainWindow = nullptr;
	WindowBase* findById(const string& id)
	{
		for(WindowBase* e : elements)
		{
			if(e->getId() == id) return e;
		}
		return nullptr;
	}
	bool isCellAvailable(Window* parent, int r, int c)
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
	
public:
	~WindowManager()
	{
		for(WindowBase* e : elements) delete e;
	}
	void addWindow(string id, int rows, int cols, string parentId="-1", int row=-1, int col=-1)
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
	void addText(string id, string text, string parentId, int row, int col)
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
	void addTable(string id, int rows, int cols, string parentId, int row, int col)
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
	void addButton(string id, string text, string parentId, int row, int col)
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
	void drawAll()
	{
		if(mainWindow) mainWindow->draw();
		else cerr<<"No main window to draw!\n";
	}
};

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
