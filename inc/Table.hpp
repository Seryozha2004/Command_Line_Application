#ifndef TABLE_HPP
#define TABLE_HPP

#include "WindowBase.hpp"
#include <iostream>

using namespace std;

class Table : public WindowBase {
private:
	int rowCount, colCount;
public:
	Table(string id, int rowCount, int colCount, WindowBase* parent, int row, int col);
	void draw(int indent = 0) const override;
};

#endif
