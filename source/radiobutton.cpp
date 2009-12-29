#include "tobkit/radiobutton.h"
#include "tobkit/gui.h"

#include "radiobutton_unchecked_raw.h"
#include "radiobutton_checked_raw.h"
#include "radiobutton_mask_raw.h"

namespace TobKit {

/* ===================== PUBLIC ===================== */

RadioButton::RadioButton(WidgetManager *owner, string caption, int x, int y,
                RadioButtonGroup *rbg, int width, int height, bool visible)
    :Widget(x, y, width, height, owner, 0, visible),
	_rbg(rbg), _active(false), _label(caption)
{
	_rbg->add(this);

	if(width == -1) {
        _width = getStringWidth(_label) + 13;
    }
    if(height == -1) {
        _height = 14;
    }

	pleaseDraw();
}

// Event calls
void RadioButton::penDown(int px, int py) {
	_rbg->setChecked(this);
}

void RadioButton::setCaption(const string &caption)
{
	_label = caption;
	pleaseDraw();
}

void RadioButton::setChecked(bool active)
{
	_active = active;
	pleaseDraw();
}

/* ===================== PRIVATE ===================== */

void RadioButton::draw(void)
{
	// Draw the dot
	//drawFullBox(2, 2, 7, 7, col);
	drawGradient(_theme->gradient_ctrl ,0, 0, 9, 9);

	if(_owner->hasDarkBG()) {
	    drawMonochromeIcon(0, 0, 9, 9, radiobutton_mask_raw, _theme->col_bg);
	    drawString(_label, 13, 0, 255, _theme->col_lighter_bg);
	} else {
	    drawMonochromeIcon(0, 0, 9, 9, radiobutton_mask_raw, _theme->col_lighter_bg);
	    drawString(_label, 13, 0, 255, _textcolor);
	}

	if(_active) {
	    drawMonochromeIcon(0, 0, 9, 9, radiobutton_checked_raw);
	} else {
	    drawMonochromeIcon(0, 0, 9, 9, radiobutton_unchecked_raw);
	}

	/*drawHLine(3, 1, 2, _theme->col_outline);
	drawLine(3, 9, 5, 1, _theme->col_outline);
	drawLine(1, 3, 5, 0, _theme->col_outline);
	drawLine(9, 3, 5, 0, _theme->col_outline);
	
	drawPixel(2, 2, _theme->col_outline);
	drawPixel(8, 2, _theme->col_outline);
	drawPixel(2, 8, _theme->col_outline);
	drawPixel(8, 8, _theme->col_outline);
	*/
	// Filled or not
	//if(_active == true) {
	//	drawFullBox(4, 4, 3, 3, _theme->col_outline);
	//}
	
	// Text

}

}
