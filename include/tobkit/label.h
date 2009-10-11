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

class Label: public Widget {

	public:
	    Label(WidgetManager *owner, const string &caption, int x, int y,
	            bool has_border=false, int width=-1, int height=-1,
	            bool visible=true);

		~Label(void);

		// Drawing request
		void pleaseDraw(void);

		// Event calls
		void penDown(u8 x, u8 y);

		void setCaption(const string &caption);
		const string &getCaption(void);

		// Signals
		sigc::signal<void> signal_pushed;

	private:
	    void draw(void);

		string _caption;
		bool _has_border;
};

};

#endif
