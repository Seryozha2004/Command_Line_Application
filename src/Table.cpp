#include "../inc/Table.hpp"
using namespace std;

Table::Table(string id, int rowCount, int colCount, WindowBase* parent, int row, int col)
	: WindowBase(id, row, col, parent), rowCount(rowCount), colCount(colCount) {}
void Table::draw(int indent) const
{
	cout<<string(indent, ' ')<<"[Table] ID: "<<id
		<<" Size: "<<rowCount<<"x"<<colCount
		<<" Pos: ("<<row<<","<<col<<")\n";
}
