#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <nds.h>

#include "tobkit/label.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

Label::Label(WidgetManager *owner, const string &caption, int x, int y,
    bool has_border, int width, int height, bool visible)
    :Widget(x, y, width, height, owner, 0, visible),
    _caption(caption), _has_border(has_border)
{
    if(width == -1) {
        _width = getStringWidth(_caption) + 2;
    }
    if(height == -1) {
        _height = 14;
    }

    pleaseDraw();
}

Label::~Label(void)
{

}

// Drawing request
void Label::pleaseDraw(void) {
	if(isExposed()) {
		draw();
	}
}

// Event calls
void Label::penDown(u8 x, u8 y)
{
	signal_pushed();
}

void Label::setCaption(const string &caption)
{
	_caption = caption;
	draw();
}

const string &Label::getCaption(void) {
	return _caption;
}

/* ===================== PRIVATE ===================== */

void Label::draw(void)
{
    if(_has_border) {
        drawFullBox(0, 0, _width, _height, _theme->col_lighter_bg);
        drawBorder();
    } else {
        drawFullBox(0, 0, _width, _height, _bgcolor);
    }

    if(_caption != "") {
        drawString(_caption, 2, 2, _width, _textcolor);
    }
}

};
