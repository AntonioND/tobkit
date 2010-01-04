#include <string>
#include "tobkit/gui.h"
#include "tobkit/groupbox.h"

using namespace std;

namespace TobKit
{

/* ===================== PUBLIC ===================== */

GroupBox::GroupBox(WidgetManager *owner, const string &caption, int x, int y, int width, int height, bool visible)
      :Widget(x, y, width, height, owner, NULL, visible),
       _caption(caption)
{
    pleaseDraw();
}

GroupBox::~GroupBox()
{

}

void GroupBox::setCaption(const string &caption)
{
	_caption = caption;
	pleaseDraw();
}

/* ===================== PRIVATE ===================== */

void GroupBox::draw(void)
{
    u16 col_line, col_bg, col_text;
    if(_owner->hasDarkBG()) {
        col_line = _theme->col_lighter_bg;
        col_bg = _theme->col_bg;
        col_text = _theme->col_lighter_bg;
    } else {
        col_line = _theme->col_bg;
        col_bg = _theme->col_light_bg;
        col_text = _textcolor;
    }
	drawBox(0, 4, _width, _height, col_line);
	u16 strwidth = getStringWidth(_caption);
	drawFullBox(10, 0, strwidth+2, 10, col_bg);
	drawString(_caption, 11, 0, _width - 12, col_text);
}

};
