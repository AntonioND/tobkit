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
        /**
         * Creates a BitButton
         * \param owner the GUI that the BitButton belongs to
         * \param bitmap the image on the BitButton
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the BitButton
         * \param height height of the BitButton
         * \param bmpwidth width of the bitmap in pixels
         * \param bmpheight height of the bitmap in pixels
         * \param bmpx x-position of the bitmap on the BitButton
         * \param bmpy y-position of the bitmap on the BitButton
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         * \param visible if the BitButton is drawn and responds to input
         */
	    BitButton(WidgetManager *owner, const u8 *bitmap, int x, int y, int width=17, int height=17,
	            int bmpwidth=13, int bmpheight=13, int bmpx=2, int bmpy=2, u16 listening_buttons=0, bool visible=true);

		/**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penDown(int x, int y);

		/**
         * The pen is lifted from the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penUp();

		/**
         * A (hardware) button that the (software) Button reacts to is pressed.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void buttonPress(u16 button);

		/**
         * This signal is emitted if the BitButton is pushed.
         */
        sigc::signal<void> signal_pushed;

	private:
		void draw(void);

		bool _pen_is_down;
		const u8 *_bitmap;
		int _bmpwidth, _bmpheight, _bmpx, _bmpy;
};

};

#endif
