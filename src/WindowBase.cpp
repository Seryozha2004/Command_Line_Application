#include "../inc/WindowBase.hpp"
using namespace std;

WindowBase::WindowBase(string id, int row, int col, WindowBase* parent)
	: id(id), row(row), col(col), parent(parent) {}
WindowBase::~WindowBase() {}
string WindowBase::getId() const { return id; }
WindowBase* WindowBase::getParent() const { return parent; }
int WindowBase::getRow() const { return row; }
int WindowBase::getCol() const { return col; }
