#include "../inc/Text.hpp"
using namespace std;

Text::Text(string id, string text, WindowBase* parent, int row, int col)
	: WindowBase(id, row, col, parent), text(text) {}
void Text::draw(int indent) const
{
	cout<<string(indent, ' ')<<"[Text] ID: "<<id
		<<" \""<<text<<"\" Pos: ("<<row<<","<<col<<")\n";
}
