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

#ifndef _TYPEWRITER_H_
#define _TYPEWRITER_H_

#include "tobkit/widget.h"
#include "tobkit/label.h"
#include "tobkit/button.h"
#include "tobkit/gui.h"
#include "tobkit/widgetmanager.h"

namespace TobKit {

class Typewriter: public Widget, public WidgetManager {
	public:
	    Typewriter(WidgetManager *owner, const string &message, const string &text="");
		~Typewriter(void);

		// Set up the keyboard graphics using a tiled background
        void setupPalette(void);
        void setupTileBg(void);

		// Event calls
		void penDown(int x, int y);
		void penUp(int x, int y);

		void buttonPress(u16 button);

		void setText(const string &text);
		const string &getText(void);

		void show(void);
		void reveal(void);

		// Signals
		sigc::signal<void> signal_ok, signal_cancel;

	private:
	    enum Mode {Normal, Shift, Caps};

		u16 *char_base, *map_base;
		int pal_id_normal, pal_id_highlight;

		u16 col_bg;

		u8 kx, ky; // Keyboard offset in tiles (1t=8px)

		Label *label, *msglabel;
		Button *buttonok, *buttoncancel;

		Mode mode;
		vuint16 *trans_reg_x, *trans_reg_y;

		u8 tilex, tiley;

		string _text;
		u16 cursorpos;

		void draw(void);
		void redraw(void);
		void drawCursor(void);
		void setTile(int x, int y, int pal);
};

};

#endif
