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

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "widget.h"
#include <stdio.h>
#include <vector>

class RadioButton: public Widget {
	public:
		class RadioButtonGroup {
			public:
				RadioButtonGroup();
				
				void add(RadioButton *rb);
				void pushed(RadioButton *rb);
				void setActive(u8 idx);
				void registerChangeCallback(void (*onChange_)(u8));
	
			private:
				std::vector<RadioButton*> rbvec;
				void (*onChange)(u8);
		};
		
		RadioButton(u8 _x, u8 _y, u8 _width, u8 _height, u16 **_vram,
				RadioButtonGroup *_rbg, bool _visible=true);
		
		// Drawing request
		void pleaseDraw(void);
		
		// Event calls
		void penDown(u8 px, u8 py);
		
		void setCaption(const char *caption);
		void setActive(bool _active);
		bool getActive(void);
		
	private:
		void draw(void);
	
		RadioButtonGroup *rbg;
		bool active;
		const char *label;
};

#endif
