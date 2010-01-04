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

#include "tobkit/togglebutton.h"
#include "tobkit/tools.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

ToggleButton::ToggleButton(WidgetManager *owner, const string &caption, int x,
        int y, int width, int height, u16 listening_buttons, bool visible)
    :Widget(x, y, width, height, owner, listening_buttons, visible),
    _pen_is_down(false), _caption(caption)
{
    if(width == -1) {
        _width = getStringWidth(_caption) + 4;
    }
    if(height == -1) {
        _height = 14;
    }

    pleaseDraw();
}

void ToggleButton::penDown(int x, int y)
{
	_pen_is_down = true;
	_on = !_on;
	draw();
	signal_toggled(_on);
}

void ToggleButton::penUp()
{
	_pen_is_down = false;
	draw();
}

void ToggleButton::buttonPress(u16 button)
{
	_on = !_on;
	draw();
	signal_toggled(_on);
}

void ToggleButton::setCaption(const string &caption)
{
	_caption = caption;
}

void ToggleButton::setState(bool on)
{
	if(_on != on)
	{
		_on = on;
		draw();
		signal_toggled(_on);
	}
}

bool ToggleButton::getState(void)
{
	return _on;
}

/* ===================== PRIVATE ===================== */

void ToggleButton::draw(void)
{
	if(!isExposed()) return;

	drawGradient(_theme->gradient_ctrl, 0, 0, _width, _height, !_pen_is_down);
	drawBorder();

	u16 col = _on ? _theme->col_signal : _theme->col_text;
	drawString(_caption, MAX(2, ((_width-getStringWidth(_caption))/2) ),
	        _height/2-5, 255, col);
}

}
