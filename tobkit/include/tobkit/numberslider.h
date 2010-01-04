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

#ifndef TOBKIT_NUMBERSLIDER_H
#define TOBKIT_NUMBERSLIDER_H

#include "tobkit/widget.h"

namespace TobKit {

/**
 * Lets the user choose a number.
 * \image html numberbox.png
 */
class NumberSlider: public Widget {

	public:
        /**
         * Creates a NumberSlider
         * \param owner the GUI that the Widget belongs to
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param value the defaut value
         * \param min minimum possible value
         * \param max maximum possible value
         * \param hex whether or not the numbers are shown in hexadecimal.
         * \param width how many pixels it's wide. If this is -1 the width is determined automatically.
         * \param height how many pixels it's high.  If this is -1 the height is determined automatically.
         * \param visible if the Widget is drawn and responds to input
         */
        NumberSlider(WidgetManager *owner, int x, int y, int value, int min, int max, bool hex=false,
                int width=-1, int height=-1, bool visible=true);
	
		// Drawing request
		void pleaseDraw(void);
		
		// Event calls
		void penDown(u8 px, u8 py);
		void penUp(u8 px, u8 py);
		void penMove(u8 px, u8 py);

		void setValue(s32 val);
		s32 getValue(void);
		
		// Callback registration
		void registerChangeCallback(void (*onChange_)(s32));
		
	private:
		void draw(void);
		
		void (*onChange)(s32);
		
		s32 value;
		u8 lasty;
		bool btnstate;
		s32 min;
		s32 max;
		bool hex;
};

};

#endif
