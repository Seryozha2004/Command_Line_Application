#include "../inc/Button.hpp"
using namespace std;

Button::Button(string id, string text, WindowBase* parent, int row, int col)
	: WindowBase(id, row, col, parent), text(text) {}
void Button::draw(int indent) const
{
	cout<<string(indent, ' ')<<"[Button] ID: "<<id
		<<" \""<<text<<"\" Pos: ("<<row<<","<<col<<")\n";
}
