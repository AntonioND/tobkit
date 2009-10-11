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

#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "widget.h"
#include "gui.h"
#include "label.h"
#include "button.h"

class MessageBox: public Widget {
	public:
		MessageBox(u16 **_vram, const char *message, u8 n_buttons, ...);
		~MessageBox(void);
		
		// Drawing request
		void pleaseDraw(void);
	
		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
	
		void show(void);
		void setTheme(Theme *theme_, u16 bgcolor_);
		
	private:
		void draw(void);	
	
		GUI gui;
		//Label *label;
		const char *msg;
		Button **buttons;
		void (**callbacks)(void);
		u8 n_buttons;
};

#endif
