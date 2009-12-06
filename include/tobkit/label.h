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

#ifndef LABEL_H
#define LABEL_H

#include "tobkit/widget.h"

namespace TobKit
{

/**
 * A Label that shows some text on the screen.
 * \image html label.png
 */
class Label: public Widget {

	public:
        /**
         * Creates a Label
         * \param owner the GUI that the Label belongs to
         * \param caption the text on the Label
         * \param x x-position on the screen
         * \param y y-position on the screen
         * \param has_border whether the Label is drawn with a border (This sugests you can edit it, so if you give the Label a border, be sure to bring up a keyboard when it throws signal_pushed.)
         * \param width width of the Label
         * \param height height of the Label
         * \param visible if the Label is drawn and responds to input
         */
	    Label(WidgetManager *owner, const string &caption, int x, int y,
	            bool has_border=false, int width=-1, int height=-1,
	            bool visible=true);

		~Label(void);

		/**
		 * Request drawing the Label explicitly.
		 */
		void pleaseDraw(void);

		/**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penDown(int x, int y);

		/*
         * Change the Widget's caption
         * \param caption the new caption.
         */
		void setCaption(const string &caption);

		/**
		 * Get the Widget's caption.
		 * \returns the caption of the Widget
		 */
		const string &getCaption(void);

		/**
		 * This signal is thrown once the pen touches the Widget.
		 */
		sigc::signal<void> signal_pushed;

	private:
	    void draw(void);

		string _caption;
		bool _has_border;
};

};

#endif
