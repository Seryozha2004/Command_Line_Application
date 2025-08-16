#ifndef WINDOWBASE_HPP
#define WINDOWBASE_HPP

#include <string>
using namespace std;

class WindowBase {
protected:
	string id;
	int row, col;
	WindowBase* parent;

public:
	WindowBase(string id, int row, int col, WindowBase* parent = nullptr);
	virtual ~WindowBase();
	string getId() const;
	WindowBase* getParent() const;
	int getRow() const;
	int getCol() const;
	virtual void draw(int indent = 0) const = 0;
};

#endif
