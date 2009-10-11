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

/**********************
DS Tracker Widget Class
Has rectangular area
**********************/

#ifndef WIDGET_H
#define WIDGET_H

#include <nds.h>
#include <limits.h>
#include <sigc++/sigc++.h>
#include <string>

#include "tobkit/constants.h"
#include "tobkit/theme.h"

using namespace std;

namespace TobKit
{

class WidgetManager;
class GUI;

/**
 * \brief The base class for all TobKit Widgets. Handles input and provides a lot of useful drawing functions.
 */
class Widget
{
	friend class GUI;
	friend class WidgetManager;

	public:
		Widget(int x, int y, int width, int height, WidgetManager *owner, u16 listening_buttons=0, bool visible=true);
		virtual ~Widget(void);

		// Callback registration
		// ... is done in the class

		// Drawing request
		void pleaseDraw(void);

		// Get position
		void getPos(int *x, int *y, int *width, int *height);

		// Toggle visibility
		// Objects can be hidden either explicitly (using show/hide) or implicitly
		// (using reveal/occlude). Reveal/occlude are used eg if the object is on
		// a tab of a tabbox that is currently not selected. Show/hide is used to
		// hide controls that shall not be seen at the moment.

		// Can the widget be seen by the user?
		bool isExposed(void);

		virtual void show(void);
		virtual void hide(void);
		bool isVisible(void) { return _visible; }

		virtual void occlude(void);
		virtual void reveal(void);
		bool isOccluded(void) { return _occluded; }

		// Resize
		void resize(u16 w, u16 h);

		// Toggle enabled/disabled
		virtual void enable(void);
		virtual void disable(void);
		bool isEnabled(void) { return _enabled; }

	protected:
		WidgetManager *_owner;
	    GUI *_gui;

		Screen _screen;
		int _x, _y, _width, _height;
		bool _enabled;
		u16 **_vram;
		Theme *_theme;
		u16 _bgcolor, _textcolor; // Color of the background (for hiding the widget)

		// Event calls - called by GUI
		virtual void penDown(int px, int py) {};
		virtual void penUp(int px, int py) {};
		virtual void penMove(int px, int py) {};
		virtual void buttonPress(u16 button) {};
		virtual void buttonRelease(u16 button) {};

		// Draw utility functions
		void drawString(const string &str, int tx, int ty, uint maxwidth=255, u16 color=RGB15(0,0,0)|BIT(15));
		void drawBox(int tx, int ty, int tw, int th, u16 col=RGB15(0,0,0)|BIT(15));
		void drawFullBox(int tx, int ty, int tw, int th, u16 col);
		void drawBorder(u16 col = RGB15(0,0,0)|BIT(15));
		void drawHLine(int tx, int ty, int length, u16 col);
		void drawVLine(int tx, int ty, int length, u16 col);
		void drawLine(int tx1, int ty1, int tx2, int ty2, u16 col);
		void drawPixel(int tx, int ty, u16 col);
		void drawGradient(const std::vector<u16> &gradient, int tx, int ty, int tw, int th, bool reverse=false);
		void drawMonochromeIcon(int tx, int ty, int tw, int th, const u8 *icon);

		// Stylus utility functions
		bool isInRect(int x, int y, int x1, int y1, int x2, int y2);

		// How wide is the string when rendered?
		int getStringWidth(const string &str, u16 limit=USHRT_MAX);

        /**
         * Initialize a palette. If your widget uses a palette, put the palette initialization in this function.
         * Request the palette id from TobKit using GUI::addPalette(); Remember to the palette in the destructor using
         * GUI::delPalette()!
         */
        virtual void setupPalette(void) {};

        /**
         * Set up tile-based graphics. If your widget uses tiles, implement the initialization of the tile background
         * in this function. Request char and map bases using GUI::addTileBackground(). You do not need to clear the tile
         * background in the destructor, because this is done automatically.
         */
        virtual void setupTileBg(void) {};

        void setOverlay(void);

	private:
		bool _visible, _occluded;

		virtual void draw(void) = 0;

		// Overdraw the object with its background color when hiding it
		void overdraw(void);
};

};

#endif
