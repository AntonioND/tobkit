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

#ifndef TOBKIT_TOGGLEBUTTON_H
#define TOBKIT_TOGGLEBUTTON_H

#include "tobkit/widget.h"

namespace TobKit
{

/**
 * A button that is toggled on and off, like a switch.
 * \image html togglebutton.png
 */
class ToggleButton: public Widget
{
	public:
        /**
         * Creates a ToggleButton
         * \param owner the GUI that the Button belongs to
         * \param caption the text on the Button
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the Button
         * \param height height of the Button
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         * \param visible if the button is drawn and responds to input
         */
        ToggleButton(WidgetManager *owner, const string &caption, int x, int y,
                        int width=-1, int height=-1,
                        u16 listening_buttons=0, bool visible=true);
		
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
         * Change the ToggleButton's caption
         * \param caption the new caption.
         */
		void setCaption(const string &caption);

		/**
		 * Sets the ToggleButton to be either on or off
		 * \param on is true if it's on
		 */
		void setState(bool on);
		
		/**
		 * Get the ToggleButton's state
		 * \return true if it's on.
		 */
		bool getState(void);
	
		/**
		 * Emitted if the Button is toggled. The callee should take one boolean
		 * argument that is true if the ToggleButton is on, false if it is off.
		 */
		sigc::signal<void, bool> signal_toggled;

	protected:
		
		void draw(void);

		bool _pen_is_down, _on;
		std::string _caption;
};

};

#endif
