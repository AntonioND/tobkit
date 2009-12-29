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

#ifndef _GROUPBOX_H_
#define _GROUPBOX_H_

#include "tobkit/widget.h"

namespace TobKit
{

/** \brief A box that groups several Widgets together (purely visually).
 * \image html todo.png
 */
class GroupBox: public Widget
{
	public:
        /**
         * Creates a GroupBox
         * \param owner the GUI that the Widget belongs to
         * \param caption the text on the Widget
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the Widget
         * \param height height of the Widget
         * \param visible if the Widget is drawn and responds to input
         */
		GroupBox(WidgetManager *owner, const string &caption, int x, int y, int width, int height, bool visible=true);
		~GroupBox();
		
		/**
		 * Sets the caption of the GroupBox
		 * \param caption the new caption
		 */
		void setCaption(const string &caption);
		
	private:
		string _caption;
		
		void draw(void);
};

};

#endif
