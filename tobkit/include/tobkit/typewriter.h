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

#ifndef TOBKIT_TYPEWRITER_H
#define TOBKIT_TYPEWRITER_H

#include "tobkit/widget.h"
#include "tobkit/label.h"
#include "tobkit/button.h"
#include "tobkit/gui.h"
#include "tobkit/widgetmanager.h"

namespace TobKit {

/**
 * A dialog window showing a Typewriter for entering text on an on-screen keyboard.
 * \image html typewriter.png
 */
class Typewriter: public Widget, public WidgetManager {
	public:
        /**
         * Creates a Typewriter
         * \param owner the GUI that the Widget belongs to
         * \param message the message (or question) displayed in the title of the Tpewriter
         * \param text the initial text shown in the text box of the Typewriter
         */
	    Typewriter(WidgetManager *owner, const string &message, const string &text="");
		~Typewriter(void);

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
         * This is called to notify the widget that a hardware button was pressed.
         * \param button the hardware button that was pressed (as defined in libnds)
         */
		void buttonPress(u16 button);

		/**
		 * Sets the text in the box where the text you type is shown.
		 */
		void setText(const string &text);

		/**
		 * Gets the text in the box where the text you type is shown.
		 */
		const string &getText(void);

        /**
         * Flags the Widget as visible and draws it.
         */
        void show(void);

        /**
         * Flags the Widget as not occluded.
         */
        void reveal(void);

		// Signals
		sigc::signal<void> signal_ok, signal_cancel;

	private:
        void draw(void);
        void redraw(void);
        void drawCursor(void);
        void setTile(int x, int y, int pal);
        // Set up the keyboard graphics using a tiled background
        void setupPalette(void);
        void setupTileBg(void);

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
};

};

#endif
