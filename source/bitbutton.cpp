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
