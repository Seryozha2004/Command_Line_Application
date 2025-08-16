#include "../inc/Window.hpp"
using namespace std;

Window::Window(string id, int rowCount, int colCount, WindowBase* parent, int row, int col)
	: WindowBase(id, row, col, parent), rowCount(rowCount), colCount(colCount) {}
void Window::addChild(WindowBase* child)
{
	children.push_back(child);
}
int Window::getRowCount() const { return rowCount; }
int Window::getColCount() const { return colCount; }
const vector<WindowBase*>& Window::getChildren() const { return children; }
void Window::draw(int indent) const
{
	cout<<string(indent, ' ')<<"[Window] ID: "<<id
		<<" Size: "<<rowCount<<"x"<<colCount
		<<" Pos: ("<<row<<","<<col<<")\n";
	for(WindowBase* ch : children)
	{
		ch->draw(indent+2);
	}
}
