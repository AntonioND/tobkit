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

#ifndef HTABBOX_H
#define HTABBOX_H

#include "gui.h"
#include "widget.h"

#include <vector>

namespace TobKit
{

// Same as the tabbox, but with tabs on the left instead of on topHTabBox *
// Also, the icons are smaller, because I need to save space :-)

class HTabBox: public Widget {
	public:
		HTabBox(u8 _x, u8 _y, u8 _width, u8 _height, u16 **_vram, bool _visible=true);
		
		void addTab(const u8 *icon);
		
		// Adds a widget and specifies which button it listens to
		// Touches on widget's area are redirected to the widget
		void registerWidget(Widget *w, u16 listeningButtons, u8 tabidx, u8 screen=SUB_SCREEN);
		
		// Event calls
		void penDown(u8 px, u8 py);
		void penUp(u8 px, u8 py);
		void penMove(u8 px, u8 py);
		void buttonPress(u16 buttons);
		
		// Callback registration
		void registerTabChangeCallback(void (*onTabChange_)(u8 tab));
		
		// Drawing request
		void pleaseDraw(void);
		
		void show(void);
		void hide(void);
		void reveal(void);
		void occlude(void);
		
		void setTheme(Theme *theme_, u16 bgcolor_);
		
	private:
		void draw(void);
		void updateVisibilities(void);
		
		u8 currenttab;
		std::vector<const u8*> icons;
		std::vector<GUI> guis;
		
		void (*onTabChange)(u8 tab);
};

};

#endif
