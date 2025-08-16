#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "WindowBase.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Window : public WindowBase {
private:
        int rowCount, colCount;
        vector<WindowBase*> children;

public:
        Window(string id, int rowCount, int colCount, WindowBase* parent=nullptr, int row=-1, int col=-1);
        void addChild(WindowBase* child);
        int getRowCount() const;
        int getColCount() const;
        const vector<WindowBase*>& getChildren() const;
        void draw(int indent = 0) const override;
};

#endif

