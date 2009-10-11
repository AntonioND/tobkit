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

void Button::penUp(int x, int y)
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
