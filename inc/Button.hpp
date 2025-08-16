#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "WindowBase.hpp"
#include <iostream>
#include <string>

using namespace std;

class Button : public WindowBase {
private:
	string text;
public:
	Button(string id, string text, WindowBase* parent, int row, int col);
	void draw(int indent = 0) const override;
};

#endif
