#ifndef TEXT_HPP
#define TEXT_HPP

#include "WindowBase.hpp"
#include <iostream>
#include <string>

using namespace std;

class Text : public WindowBase {
private:
	string text;
public:
	Text(string id, string text, WindowBase* parent, int row, int col);
	void draw(int indent = 0) const override;
};

#endif
