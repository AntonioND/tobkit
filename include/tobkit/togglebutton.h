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

#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "widget.h"

class ToggleButton: public Widget {
	public:
		ToggleButton(u8 _x, u8 _y, u8 _width, u8 _height, u16 **_vram, bool _visible=true);
	
		// Callback registration
		void registerToggleCallback(void (*onToggle_)(bool));
		
		// Drawing request
		void pleaseDraw(void);
		
		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void buttonPress(u16 button);
		
		void setCaption(const char *_caption);
		
		void setState(bool _on);
		bool getState(void);
	
	private:
		void (*onToggle)(bool);
		
		bool penIsDown;
	
		bool on;	
	
		void draw(void);
		
		char *caption;
};

#endif
