/*
 * TobKit - A simple user interface toolkit for Nintendo DS homebrew
 *                   Copyright 2005-2009 Tobias Weyand (me@tobw.net)
 *                                   http://code.google.com/p/tobkit
 *
 * TobKit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * TobKit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with TobKit.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

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
        _width = getStringWidth(_caption) + 3;
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
void Label::penDown(int x, int y)
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
