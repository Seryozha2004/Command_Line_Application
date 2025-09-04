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
	WindowManager() {}
	WindowManager(const WindowManager&) = delete;
	WindowManager& operator = (const WindowManager&) = delete;
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
	static WindowManager& getInstance()
	{
		static WindowManager instance;
		return instance;
	}
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

class Command {
public:
	virtual ~Command() {}
	virtual bool validate(istringstream& iss) = 0;
	virtual void execute() = 0;
};

class AddWindowCommand : public Command {
private:
	string id, parentId;
	int rows, cols, r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override
	{
		if(!(iss>>id>>rows>>cols)) return false;
		parentId="-1"; 
		r=-1; 
		c=-1;
		iss>>parentId>>r>>c;
		valid = true;
		return true;
	}
	void execute() override
	{
		if(valid) WindowManager::getInstance().addWindow(id, rows, cols, parentId, r, c);
	}
};

class AddTextCommand : public Command {
private:
	string id, text, parentId;
	int r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override 
	{
		if(!(iss>>id>>text>>parentId>>r>>c)) return false;
		valid = true;
		return true;
	}
	void execute() override
	{
		if(valid) WindowManager::getInstance().addText(id, text, parentId, r, c);
	}
};

class AddTableCommand : public Command {
private:
	string id, parentId;
	int rows, cols, r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override
	{
		if(!(iss>>id>>rows>>cols>>parentId>>r>>c)) return false;
		valid = true;
		return true;
	}
	void execute() override
	{
		if(valid) WindowManager::getInstance().addTable(id, rows, cols, parentId, r, c);
	}
};

class AddButtonCommand : public Command {
private:
	string id, text, parentId;
	int r, c;
	bool valid = false;
public:
	bool validate(istringstream& iss) override
	{
		if(!(iss>>id>>text>>parentId>>r>>c)) return false;
		valid = true;
		return true;
	}
	void execute() override
	{
		if(valid) WindowManager::getInstance().addButton(id, text, parentId, r, c);
	}
};

class DrawCommand : public Command {
public:
	bool validate(istringstream&) override { return true; }
	void execute() override { WindowManager::getInstance().drawAll(); }
};

class CommandFactory {
public:
	static Command* createCommand(const string& cmdName)
	{
		if(cmdName == "add_window") return new AddWindowCommand();
		else if(cmdName == "add_text") return new AddTextCommand();
		else if(cmdName == "add_table") return new AddTableCommand();
		else if(cmdName == "add_button") return new AddButtonCommand();
		else if(cmdName == "draw") return new DrawCommand();
		return nullptr;
	}
};

int main()
{
	string line;
	while(true)
	{
		cout<<"> ";
		if(!getline(cin, line)) break;
		if(line == "quit") break;
		istringstream iss(line);
		string cmdName;
		iss>>cmdName;
		Command* cmd = CommandFactory::createCommand(cmdName);
		if(!cmd)
		{
			cerr<<"Unknown command!\n";
			continue;
		}
		if(!cmd->validate(iss))
		{
			cerr<<"Invalid arguments for command: "<<cmdName<<endl;
			delete cmd;
			continue;
		}
		cmd->execute();
		delete cmd;
	}
	return 0;
}
