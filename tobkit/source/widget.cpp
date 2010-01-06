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

#include "tobkit/widget.h"
#include "tobkit/fontchars.h"
#include "tobkit/tools.h"
#include "font_8x11_raw.h"
#include "tobkit/gui.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

Widget::Widget(int x, int y, int width, int height, WidgetManager *owner, u16 listening_buttons, bool visible)
	:_owner(owner), _screen(owner->_screen), _x(x), _y(y), _width(width), _height(height), _enabled(true), _visible(visible), _occluded(false)
{
	// Add yourself to the GUI
	_owner->addWidget(this, listening_buttons);

	// Get info from the GUI
	_theme = _owner->_theme;
	_bgcolor = _owner->_bg_color;
	_textcolor = _owner->_text_color;
	_gui = _owner->_gui;
    _vram = &_gui->_vram;
}

Widget::~Widget(void)
{
    _owner->removeWidget(this);
}

void Widget::pleaseDraw(void)
{
    if(isExposed()) {
        draw();
    }
}

// Get position
void Widget::getPos(int *x, int *y, int *width, int *height)
{
	*x = _x;
	*y = _y;
	*width = _width;
	*height = _height;
}

bool Widget::isExposed(void)
{
	return _visible && !_occluded;
}

// Toggle visibility
void Widget::show(void)
{
	if(!_visible) {
		_visible = true;
		if(!_occluded) {
			pleaseDraw();
		}
	}
}

void Widget::hide(void)
{
	if(isExposed()) {
		overdraw();
	}
	_visible = false;
}

void Widget::occlude(void)
{
	if(isExposed()) {
			overdraw();
	}
	_occluded = true;
}

void Widget::reveal(void)
{
	if(_occluded) {
		_occluded = false;
		if(_visible) {
			pleaseDraw();
		}
	}
}

void Widget::resize(u16 w, u16 h)
{
	overdraw();
	_width = w;
	_height = h;
	pleaseDraw();
}

// Toggle enabled/disabled
void Widget::enable(void)
{
	if(!_enabled) {
		_enabled = true;
		pleaseDraw();
	}
}

void Widget::disable(void)
{
	if(_enabled) {
		_enabled = false;
		pleaseDraw();
	}
}

/* ===================== PROTECTED ===================== */

// Draw utility functions

void Widget::drawString(const string &str, int tx, int ty, uint maxwidth, u16 color)
{
	int charidx, i, j;
	uint drawpos = 0; u8 col;
	char *charptr;
	int startline = (ty > 0) ? 0 : -ty;
	int endline = (ty + FONT_HEIGHT < _height) ? FONT_HEIGHT : (_height - ty);
	if(endline <= startline) return;

	for(uint pos = 0; pos < str.length(); ++pos) {
		charptr = strchr(fontchars, str[pos]);
		if(charptr==0) {
			charidx = 66; // '?'
		} else {
			charidx = charptr - fontchars;
		}

		if(drawpos + charwidths_8x11[charidx] >= maxwidth) {
		    break;
		}

		for(j = startline; j < endline; ++j) {
			for(i = 0; i < FONT_WIDTH; ++i) {
				// Print a character from the bitmap font
				// each char is 8 pixels wide, and 8 pixels
				// are in a byte.
				col = font_8x11_raw[N_FONT_CHARS * j + charidx];
				if(col & BIT(i)) {
					(*_vram)[SCREEN_WIDTH*(j + _y + ty) + (i + _x + tx + drawpos)] = color;
				}
			}
		}

		drawpos += charwidths_8x11[charidx] + 1;
	}
}

void Widget::drawBox(int tx, int ty, int tw, int th, u16 col)
{
	for(int i=0;i<tw;++i) {
		(*_vram)[SCREEN_WIDTH*(_y+ty)+i+(_x+tx)] = col;
		(*_vram)[SCREEN_WIDTH*((_y+ty)+th-1)+i+(_x+tx)] = col;
	}
	for(int j=0;j<th;++j) {
		(*_vram)[SCREEN_WIDTH*((_y+ty)+j)+(_x+tx)] = col;
		(*_vram)[SCREEN_WIDTH*((_y+ty)+j)+(_x+tx)+tw-1] = col;
	}
}

void Widget::drawFullBox(int tx, int ty, int tw, int th, u16 col)
{
	for(int i=0;i<tw;++i) {
		for(int j=0;j<th;++j) {
			(*_vram)[SCREEN_WIDTH*(_y+ty+j)+i+(_x+tx)] = col;
		}
	}
}

void Widget::drawBorder(u16 col) {
	drawBox(0, 0, _width, _height, col);
}

void Widget::drawHLine(int tx, int ty, int length, u16 col)
{
	for(int i=0;i<length;++i) {
		(*_vram)[SCREEN_WIDTH*(_y+ty)+i+(_x+tx)] = col;
	}
}

void Widget::drawVLine(int tx, int ty, int length, u16 col)
{
	for(int i=0;i<length;++i) {
		(*_vram)[SCREEN_WIDTH*(_y+ty+i)+(_x+tx)] = col;
	}
}

void Widget::drawLine(int tx1, int ty1, int tx2, int ty2, u16 col)
{
	// Bresenham algorithm
	u32 x1, y1, x2, y2;
	x1 = tx1 + _x;
	x2 = tx2 + _x;
	y1 = ty1 + _y;
	y2 = ty2 + _y;

	// Guarantees that all lines go from left to right
	if ( x2 < x1 ) {
		u32 tmp;
		tmp = x2; x2 = x1; x1 = tmp;
		tmp = y2; y2 = y1; y1 = tmp;
	}

	s32 dy,dx;
	dy = y2 - y1;
	dx = x2 - x1;

	// If the gradient is greater than one we have to flip the axes
	if ( abs(dy) < dx )	{
		u16 xp,yp;
		s32 d;
		s32 add = 1;

		xp = x1;
		yp = y1;

		if(dy < 0) {
			dy = -dy;
			add =- 1;
		}

		d = 2*dy - dx;

		for(; xp<=x2; xp++)	{
			if(d > 0)
			{
				yp += add;
				d -= 2 * dx;
			}

			(*_vram)[SCREEN_WIDTH*yp+xp] = col;

			d += 2 * dy;
		}
	} else {
		u16 tmp;
		tmp = x1; x1 = y1; y1 = tmp;
		tmp = x2; x2 = y2; y2 = tmp;

		if ( x2 < x1 )	{
			tmp = x2; x2 = x1; x1 = tmp;
			tmp = y2; y2 = y1; y1 = tmp;
		}

		u16 xp,yp;
		s32 d;

		dy = y2 - y1;
		dx = x2 - x1;

		s32 add = 1;

		if(dy < 0) {
			dy = -dy;
			add=-1;
		}

		xp = x1;
		yp = y1;

		d = 2 * dy - dx;

		for(xp=x1; xp<=x2; xp++) {
			if(d > 0) {
				yp += add;
				d -= 2 * dx;
			}

			(*_vram)[SCREEN_WIDTH*xp+yp] = col;

			d += 2 * dy;
		}
	}
}

void Widget::drawPixel(int tx, int ty, u16 col) {
	(*_vram)[SCREEN_WIDTH*(_y+ty)+_x+tx] = col;
}

void Widget::drawGradient(const std::vector<u16> &gradient, int tx, int ty, int tw, int th, bool reverse)
{
	int n_shades = gradient.size();
	u16 *vram_ptr = *_vram + SCREEN_WIDTH*(_y+ty) + _x + tx;
	int step = n_shades / th;

	int start, end, inc;
	if(!reverse) {
	    start = 0; end = th; inc = 1;
	} else {
	    start = th; end = 0; inc = -1;
	}
	for(int y = start; y != end; y += inc) {
	    for(int x=0;x<tw;++x) {
	        *(vram_ptr++) = gradient[y * step];
	    }
	    vram_ptr += SCREEN_WIDTH - tw;
	}
}

// How wide is the string when rendered?
int Widget::getStringWidth(const string &str, u16 limit)
{
	int i,res=0,charidx,len = str.size();
	if((limit!=USHRT_MAX)&&(limit<len)) {
		len = limit;
	}
	char *charptr;
	for(i=0;i<len;++i) {
		charptr = strchr(fontchars, str[i]);
		if(charptr==0) {
			charidx = 39; // '_'
		} else {
			charidx = charptr - fontchars;
		}
		res += charwidths_8x11[charidx] + 1;
	}
	return res;
}

void Widget::drawMonochromeIcon(int tx, int ty, int tw, int th, const u8 *icon, u16 color)
{
	for(int j=0;j<th;++j) {
		for(int i=0;i<tw;++i) {
			u16 pixelidx = tw*j+i;
			if(icon[pixelidx/8] & BIT(pixelidx%8) ) {
				(*_vram)[SCREEN_WIDTH*(_y+ty+j)+_x+tx+i] = color;
			}
		}
	}
}

// Stylus utility functions
bool Widget::isInRect(int x, int y, int x1, int y1, int x2, int y2)
{
	return ( (x >= x1) && (x <= x2) && (y >= y1) && (y <= y2) );
}

void Widget::setOverlay(void)
{
    _owner->setOverlayWidget(this);
}

/* ===================== PRIVATE ===================== */

void Widget::overdraw(void)
{
	drawFullBox(0, 0, _width, _height, _bgcolor);
}

};
