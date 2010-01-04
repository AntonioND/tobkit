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

#ifndef TOBKIT_CHECKBOX_H
#define TOBIKT_CHECKBOX_H

#include "tobkit/widget.h"

#include <string>

namespace TobKit{

/**
 * A checkable box with a label next to it.
 * \image html checkbox.png
 */
class CheckBox: public Widget
{
	public:
        /**
         * Creates a CheckBox.
         * \param owner the GUI that the Widget belongs to
         * \param caption the text on the CheckBox
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param checked whether or not it's checked
         * \param width how many pixels it's wide.  If this is -1 the width is determined automatically.
         * \param height how many pixels it's high.  If this is -1 the height is determined automatically.
         * \param visible if the Widget is drawn and responds to input
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         */
        CheckBox(WidgetManager *owner, string caption, int x, int y, bool checked=false, int width=-1, int height=-1,
                bool visible=true, u16 listening_buttons=0);
		
		/**
		 * Change the CheckBox's caption
         * \param caption the new caption.
		 */
		void setCaption(string caption);
		
		/**
		 * Sets the checked state.
		 * \param checked whether the CheckBox is checked
		 */
		void setChecked(bool checked);
		
        /**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penDown(int x, int y);

        /**
         * Signals when the CheckBox is pushed.
         */
        sigc::signal<void, bool> signal_pushed;

	private:
        void draw(void);

		std::string _caption;
		bool _checked;
};

};

#endif
