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

#include "tobkit/widget.h"

#include <string>

namespace TobKit{

/**
 * A checkable box with a label next to it.
 * \image html todo.png
 */
class CheckBox: public Widget
{
	public:
        /**
         * Creates a CheckBox. This is only called from the constructors of subclasses.
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the Widget
         * \param height height of the Widget
         * \param owner the GUI that the Widget belongs to
         * \param visible if the Widget is drawn and responds to input
         * \param albino whether the Widget is bright on a dark background
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         */
        CheckBox(WidgetManager *owner, string caption, int x, int y, bool checked=false, int width=-1, int height=-1,
                bool visible=true, bool albino=false, u16 listening_buttons=0);
		~CheckBox();
		
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
		
        sigc::signal<void, bool> signal_pushed;

	private:
        void draw(void);

		std::string _caption;
		bool _checked;
		bool _albino;
};

};

#endif
