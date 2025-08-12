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
	void draw(int indent = 0) const override 
	{
		cout<<string(indent, ' ')<<"[Window] ID: "<<id
			<<" Size: "<<rowCount<<"x"<<colCount
			<<" Pos: ("<<row<<","<<col<<")\n";
		for(auto ch : children)
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
	WindowBase* findById(const string& id)
	{
		for(auto e : elements)
		{
			if(e->getId() == id) return e;
		}
		return nullptr;
	}
	
public:
	~WindowManager()
	{
		for(auto e : elements) delete e;
	}
	void addWindow(string id, int rows, int cols, string parentId="-1", int row=-1, int col=-1)
	{
		WindowBase* parent = nullptr;
		if(parentId != "-1") parent = findById(parentId);
		Window* win = new Window(id, rows, cols, parent, row, col);
		elements.push_back(win);
		if(parent)
		{
			auto pw = dynamic_cast<Window*>(parent);
			if(pw) pw->addChild(win);
		}
	}
	void addText(string id, string text, string parentId, int row, int col)
	{
		auto parent = findById(parentId);
		if(!parent)
		{
			cerr<<"Parent window not found!\n";
			return;
		}
		Text* t = new Text(id, text, parent, row, col);
		elements.push_back(t);
		auto pw = dynamic_cast<Window*>(parent);
		if(pw) pw->addChild(t);
	}
	void addTable(string id, int rows, int cols, string parentId, int row, int col)
	{
		auto parent = findById(parentId);
		if(!parent)
		{
			cerr<<"Parent window not found!\n";
			return;
		}
		Table* tbl = new Table(id, rows, cols, parent, row, col);
		elements.push_back(tbl);
		auto pw = dynamic_cast<Window*>(parent);
		if(pw) pw->addChild(tbl);
	}
	void addButton(string id, string text, string parentId, int row, int col)
	{
		auto parent = findById(parentId);
		if(!parent)
		{
			cerr<<"Parent window not found!\n";
			return;
		}
		Button* btn = new Button(id, text, parent, row, col);
		elements.push_back(btn);
		auto pw = dynamic_cast<Window*>(parent);
		if(pw) pw->addChild(btn);
	}
	void drawAll()
	{
		for(auto e : elements)
		{
			if(!e->getParent()) e->draw();
		}
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
