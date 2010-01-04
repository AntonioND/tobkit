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
 * \image html numberslider.png
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
         * \param width how many pixels it's wide. If this is -1 the width is
         *        determined automatically.
         * \param visible if the Widget is drawn and responds to input
         */
        NumberSlider(WidgetManager *owner, int x, int y, int value, int min,
                int max, bool hex=false, int width=-1,
                bool visible=true);
		
        /**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penDown(int px, int py);

		/**
         * This is called to notify the widget that the pen was lifted.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penUp();

	      /**
           * This is called to notify the widget that the pen was moved.
           * This method is called by the GUI.
           * You only need this method if you want to simulate the event manually.
           * \param px the x-position of the pen
           * \param py the y-position of the pen
           */
		void penMove(int px, int py);

		/**
		 * Set the value of the NumberSlider
		 * \param val the new value
		 */
		void setValue(int val);

		/**
		 * Get the value from the NumberSlider
		 * \return the value
		 */
		int getValue(void);
		
		/**
         * Signals when the NumberSlider's value changes.
         */
        sigc::signal<void, int> signal_changed;
		
	private:
		void draw(void);
		
		int _value, _lasty;
		bool _btnstate;
		int _min, _max;
		bool _hex;
		std::string _printfstr;
};

};

#endif
