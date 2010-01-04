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

#include "tobkit/togglebitbutton.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

ToggleBitButton::ToggleBitButton(WidgetManager *owner, const u8 *bitmap, int x,
        int y, int width, int height, int bmpwidth, int bmpheight, int bmpx,
        int bmpy, u16 listening_buttons, bool visible)
    :ToggleButton(owner, "", x, y, width, height,listening_buttons, visible),
    _bitmap(bitmap), _bmpwidth(bmpwidth), _bmpheight(bmpheight),
    _bmpx(bmpx), _bmpy(bmpy)
{
    pleaseDraw();
}

/* ===================== PRIVATE ===================== */

void ToggleBitButton::draw(void)
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

    u16 col =  _on ? _theme->col_signal : _theme->col_text;
    drawMonochromeIcon(_bmpx, _bmpy, _bmpwidth, _bmpheight, _bitmap, col);
}

}
