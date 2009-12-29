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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

#include "tobkit/checkbox.h"
#include "tobkit/gui.h"
#include "haken_raw.h"

using namespace std;

namespace TobKit {

/* ===================== PUBLIC ===================== */

CheckBox::CheckBox(WidgetManager *owner, string caption, int x, int y, bool checked, int width, int height,
        bool visible, u16 listening_buttons)
    :Widget(x, y, width, height, owner, listening_buttons, visible),
     _caption(caption), _checked(checked)
{
    if(width == -1) {
        _width = getStringWidth(_caption) + 13;
    }
    if(height == -1) {
        _height = 14;
    }

    pleaseDraw();
}

CheckBox::~CheckBox()
{
}

void CheckBox::setCaption(string caption)
{
	_caption = caption;
}

void CheckBox::setChecked(bool checked)
{
	_checked = checked;
	draw();
}

// Event calls
void CheckBox::penDown(int x, int y)
{
	_checked = !_checked;
	signal_pushed(_checked);
	draw();
}

/* ===================== PRIVATE ===================== */

void CheckBox::draw(void)
{
	// Draw the box
	if(_enabled)
		drawGradient(_theme->gradient_ctrl ,2, 4, 7, 7);
	else
		drawGradient(_theme->gradient_ctrl_disabled, 2, 4, 7, 7);
	
	drawBox(1, 3, 9, 9, _theme->col_outline);
	
	// Clear up
	drawFullBox(0, 0, 11, 3, _bgcolor);
	
	u16 col = _owner->hasDarkBG() ? _theme->col_lighter_bg : _textcolor;

	// Checked or not
	if(_checked)
		drawMonochromeIcon(1, 0, 10, 10, haken_raw);
	
	// Text
	drawString(_caption, 13, 2, 255, col);
}

};
