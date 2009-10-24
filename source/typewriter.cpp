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

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tobkit/typewriter.h"
#include "tobkit/typewriter.hit.h"
#include "tobkit/typewriter.map.h"
#include "tobkit/typewriter.pal.h"
#include "tobkit/typewriter.raw.h"

#define BSP	0x8 // Backspace
#define CAP	0x2 // Caps
#define RET	'\n' // Enter
#define SHF	0x4 // Shift
#define NOK 0x0 // No key

#define MAX_TEXT_LEN	20

#define TW_WIDTH	216
#define TW_HEIGHT	127

namespace TobKit
{

/* ===================== PUBLIC ===================== */

Typewriter::Typewriter(WidgetManager *owner, const string &message, const string &text)
    :Widget((SCREEN_WIDTH-TW_WIDTH)/2, (SCREEN_HEIGHT-TW_HEIGHT)/2-15, TW_WIDTH, TW_HEIGHT, owner, 0, true),
    WidgetManager(*owner, Widget::_theme->col_light_bg, Widget::_theme->col_text),
    kx(_x+4), ky(_y+16),
    mode(Normal), _text(text),
    cursorpos(text.length())
{
    setOverlay();

    u8 msglength = getStringWidth(message);

    msglabel = new Label(this, message, _x+8, _y+4);
    label = new Label(this, text, _x+msglength+12, _y+4, true, TW_WIDTH-msglength-18, 15);
    buttonok = new Button(this, "OK", _x+TW_WIDTH/2+2, _y+TW_HEIGHT-12-6, 50);
    buttoncancel = new Button(this, "Cancel", _x+TW_WIDTH/2-50-2, _y+TW_HEIGHT-12-6, 50);

    buttonok->signal_pushed.connect(sigc::mem_fun(&signal_ok, &sigc::signal<void>::emit));
    buttoncancel->signal_pushed.connect(sigc::mem_fun(&signal_cancel, &sigc::signal<void>::emit));

    setupPalette();
    setupTileBg();
    pleaseDraw();
}

Typewriter::~Typewriter(void)
{
    Widget::_gui->delPalette(pal_id_normal);
    Widget::_gui->delPalette(pal_id_highlight);
    Widget::_gui->delTileBackground(this);

    delete label;
	delete msglabel;
	delete buttonok;
	delete buttoncancel;
}

void Typewriter::setupPalette(void)
{
    u16 *pal_normal, *pal_highlight;
    Widget::_gui->addPalette(&pal_normal, &pal_id_normal);
    Widget::_gui->addPalette(&pal_highlight, &pal_id_highlight);

    dmaCopy((u16*)typewriter_Palette, pal_normal, 32);
    dmaCopy((u16*)typewriter_Palette_Hilight, pal_highlight, 32);
}

void Typewriter::setupTileBg(void)
{
    int bg, bgh;
    Widget::_gui->addTileBackground(this, 7776, &char_base, 312, &map_base, &bg, &bgh);
    dmaCopy((u16*)typewriter_Tiles, char_base, 7776);
    bgSetScroll(bgh, -kx, -ky);
    bgUpdate();
}

// Event calls
void Typewriter::penDown(int x, int y)
{
	// Inside the kb?
	if((x>=kx)&&(x<=kx+26*8)&&(y>=ky)&&(y<=ky+12*8-4))
	{
		tilex = (x-kx)/8;
		tiley = (y-ky)/8;

		setTile(tilex, tiley, pal_id_highlight);

		if(tilex>=1 && tilex<=24 && tiley<=12)
		{
			char c;
			if((mode==Caps)||(mode==Shift)) {
				c = typewriter_Hit_Shift[tilex+(tiley*26)];
			} else {
				c = typewriter_Hit[tilex+(tiley*26)];
			}

			if(c==CAP) {
				if((mode==Caps)||(mode==Shift)) {
					mode = Normal;
				} else {
					mode = Caps;
				}
				redraw();
			}
			else if (c==SHF)
			{
				if((mode==Caps)||(mode==Shift)) {
					mode = Normal;
				} else {
					mode = Shift;
				}
				redraw();
			}
			else if (c==BSP)
			{
				if(cursorpos > 0) {
					for(u16 i=cursorpos-1;i<=_text.length();++i) {
						_text[i] = _text[i+1];
					}
					_text.resize(_text.length()-1);
					cursorpos--;
					label->setCaption(_text);
					drawCursor();
				}
			}
			else if (c==RET)
			{
				signal_ok();
			}
			else if(c!=NOK)
			{
				if(mode==Shift) {
					mode = Normal;
					redraw();
				}
				if(_text.length()<MAX_TEXT_LEN)
				{
				    _text.resize(_text.length()+1);
					for(u16 i=_text.length()-1;i>cursorpos;i--) {
						_text[i] = _text[i-1];
					}
					_text[cursorpos]=c;
					//_text += c;
					cursorpos++;
					label->setCaption(_text);
					drawCursor();
				}
			}
		}

	// Inside the button area?
	} else if ((x>_x)&&(x<_x+TW_WIDTH)&&(y<_y+TW_HEIGHT-4)&&(y>ky+12*8-4)) {
		WidgetManager::penDown(x, y);
	}
}

void Typewriter::penUp()
{
	setTile(tilex, tiley, pal_id_normal);
	WidgetManager::penUp();
}

void Typewriter::buttonPress(u16 button)
{
	if((button==KEY_LEFT)&&(cursorpos>0)) {
		cursorpos--;
		redraw();
	} else if((button==KEY_RIGHT)&&(cursorpos<_text.length())) {
		cursorpos++;
		redraw();
	}
}

void Typewriter::setText(const string &text)
{
	_text = text;
	cursorpos = _text.length();
	label->setCaption(text);
	redraw();
}

const string &Typewriter::getText(void) {
	return _text;
}

void Typewriter::show(void)
{
	Widget::show();
	showAll();
	redraw();
}

void Typewriter::reveal(void)
{
	Widget::reveal();
	revealAll();
	redraw();
}

/* ===================== PRIVATE ===================== */

void Typewriter::draw(void)
{
	drawFullBox(0, 0, TW_WIDTH, TW_HEIGHT, Widget::_theme->col_light_bg);
	drawBorder();
	WidgetManager::draw();

	redraw();
}

// don't draw the box new
void Typewriter::redraw(void)
{
	if(!isExposed()) {
		return;
	}

	label->pleaseDraw();
	msglabel->pleaseDraw();

	drawCursor();

	u16 map_offset;
	if((mode == Caps)||(mode == Shift)) {
		map_offset = 312;
	} else {
		map_offset = 0;
	}

    for(u8 py=0; py<12; ++py) {
		for(u8 px=0; px<26; ++px) {
		  map_base[32*py+px] = typewriter_Map[map_offset+26*py+px];
          map_base[32*py+px] |= (pal_id_normal << 12); // Write the pal index to bits 12 and 13
        }
    }
}

// Don't try this at home!
void Typewriter::drawCursor(void)
{
	int lx, ly, lw, lh;
	u16 cursorx, cursory, cursorheight;
	label->getPos(&lx, &ly, &lw, &lh);

	cursorx = lx - _x + getStringWidth(_text, cursorpos) + 1;
	cursory = ly - _y + 1;
	cursorheight = lh - 2;
	if(cursorx<lx -_x + lw) {
		drawVLine(cursorx, cursory, cursorheight, RGB15(0,0,0)|BIT(15));
	}
}

// This function is kindly sponsored by Headspin
void Typewriter::setTile(int x, int y, int pal)
{
	char c;
	int x2, y2;

	c = typewriter_Hit[(y*26)+x];

	if(!c) return;

	map_base[(y*32)+x] &= ~(7 << 12);
	map_base[(y*32)+x] |= (pal << 12);

	x2 = x; y2 = y;
	while(typewriter_Hit[(y2*26)+x2]==c)
	{
		map_base[(y2*32)+x2] &= ~(7 << 12);
		map_base[(y2*32)+x2] |= (pal << 12);

		x2 = x;
		while(typewriter_Hit[(y2*26)+x2]==c)
		{
			map_base[(y2*32)+x2] &= ~(7 << 12);
			map_base[(y2*32)+x2] |= (pal << 12);
			x2++;
		}
		x2 = x;
		while(typewriter_Hit[(y2*26)+x2]==c)
		{
			map_base[(y2*32)+x2] &= ~(7 << 12);
			map_base[(y2*32)+x2] |= (pal << 12);
			x2--;
		}

		x2 = x;
		y2++;
	}

	x2 = x; y2 = y;
	while(typewriter_Hit[(y2*26)+x2]==c)
	{
		map_base[(y2*32)+x2] &= ~(7 << 12);
		map_base[(y2*32)+x2] |= (pal << 12);

		x2 = x;
		while(typewriter_Hit[(y2*26)+x2]==c)
		{
			map_base[(y2*32)+x2] &= ~(7 << 12);
			map_base[(y2*32)+x2] |= (pal << 12);
			x2++;
		}
		x2 = x;
		while(typewriter_Hit[(y2*26)+x2]==c)
		{
			map_base[(y2*32)+x2] &= ~(7 << 12);
			map_base[(y2*32)+x2] |= (pal << 12);
			x2--;
		}

		x2 = x;
		y2--;
	}
}

};

