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

#include "tobkit/bitbutton.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

BitButton::BitButton(WidgetManager *owner, const u8 *bitmap, int x, int y, int width, int height,
    u8 bmpwidth, u8 bmpheight, u8 bmpx, u8 bmpy, u16 listening_buttons, bool visible)
	:Widget(x, y, width, height, owner, listening_buttons, visible),
	_pen_is_down(false), _bitmap(bitmap), _bmpwidth(bmpwidth),
	_bmpheight(bmpheight), _bmpx(bmpx), _bmpy(bmpy)
{
	draw();
}

// Drawing request
void BitButton::pleaseDraw(void) {
	draw();
}

// Event calls
void BitButton::penDown(u8 x, u8 y)
{
	if(!_enabled) {
		return;
	}
	_pen_is_down = true;
	draw();
}
void BitButton::penUp(u8 x, u8 y)
{
    _pen_is_down = false;
	draw();
	signal_pushed();
}

void BitButton::buttonPress(u16 button)
{
	signal_pushed();
}

/* ===================== PRIVATE ===================== */

void BitButton::draw(void)
{
	if(!isExposed()) {
		return;
	}

	if(_enabled) {
        if(_pen_is_down) {
            drawGradient(_theme->gradient_ctrl, 0, 0, _width, _height, true);
        } else {
            drawGradient(_theme->gradient_ctrl, 0, 0, _width, _height);
        }
    } else {
        drawGradient(_theme->gradient_ctrl_disabled, 0, 0, _width, _height);
    }
	drawBorder();

	drawMonochromeIcon(_bmpx, _bmpy, _bmpwidth, _bmpheight, _bitmap);
}

}
