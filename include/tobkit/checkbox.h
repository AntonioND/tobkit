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

#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include "widget.h"

class CheckBox: public Widget
{
	public:
		CheckBox(u8 _x, u8 _y, u8 _width, u8 _height, u16 **_vram,
			 bool _visible=true, bool checked=false, bool albino=false);
		~CheckBox();
		
		void setCaption(const char *_label);
		void setChecked(bool checked_);
		
		// Drawing request
		void pleaseDraw(void);
		
		// Event calls
		void penDown(u8 px, u8 py);
		
		void registerToggleCallback(void (*onToggle_)(bool));
		
	private:
		char *label;
		bool checked;
		bool albino; // different color setting for dark bg
		
		void (*onToggle)(bool);
		
		void draw(void);
};

#endif
