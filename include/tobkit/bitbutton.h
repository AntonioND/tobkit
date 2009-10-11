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

#ifndef BITBUTTON_H
#define BITBUTTON_H

#include "tobkit/widget.h"

namespace TobKit
{

/**
 * \brief A Button with a monochrome icon on it.
 *
 * The default size for icons is 13x13 pixels. See below for instructions on how to make icons.
 * \sa \ref icons
 */
class BitButton: public Widget
{
	public:
	    BitButton(WidgetManager *owner, const u8 *bitmap, int x, int y, int width=17, int height=17,
	            u8 bmpwidth=13, u8 bmpheight=13, u8 bmpx=2, u8 bmpy=2, u16 listening_buttons=0, bool visible=true);

		// Drawing request
		void pleaseDraw(void);

		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void buttonPress(u16 button);

        // Signals
        sigc::signal<void> signal_pushed;

	private:
		void draw(void);

		bool _pen_is_down;
		const u8 *_bitmap;
		u8 _bmpwidth, _bmpheight, _bmpx, _bmpy;
};

};

#endif
