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

#include "tobkit/button.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

Button::Button(WidgetManager *owner, const string &caption, int x, int y, int width, int height,
         u16 listening_buttons, bool visible)
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

Button::~Button()
{

}

// Event calls
void Button::penDown(int x, int y)
{
    _pen_is_down = true;
    draw();
}

void Button::penUp()
{
    _pen_is_down = false;
    draw();

    signal_pushed();
}

void Button::buttonPress(u16 button)
{
    signal_pushed();
}

void Button::setCaption(const string &caption)
{
    _caption = caption;
    draw();
}

/* ===================== PRIVATE ===================== */

void Button::draw(void)
{
    if(!isExposed())
        return;

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

    drawString(_caption, (_width-getStringWidth(_caption))/2, _height/2-5);
}

};
