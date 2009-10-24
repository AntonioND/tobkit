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

#ifndef WIDGET_H
#define WIDGET_H

#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

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
        /**
         * Creates a Widget. This is only called from the constructors of subclasses.
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the Widget
         * \param height height of the Widget
         * \param owner the GUI that the Widget belongs to
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         * \param visible if the Widget is drawn and responds to input
         */
		Widget(int x, int y, int width, int height, WidgetManager *owner, u16 listening_buttons=0, bool visible=true);
		virtual ~Widget(void);

		/**
		 * Request drawing the Widget. The Widget is not drawn if it is flagged as invisible or if it is occluded.
		 */
		void pleaseDraw(void);

		/**
		 * Get the Widget geometry.
		 * \param x pointer to the variable that will hold the Widget's x-position
		 * \param y pointer to the variable that will hold the Widget's y-position
		 * \param width pointer to the variable that will hold the Widget's width
		 * \param height pointer to the variable that will hold the Widget's height
		 */
		void getPos(int *x, int *y, int *width, int *height);

		// Toggle visibility
		// Objects can be hidden either explicitly (using show/hide) or implicitly
		// (using reveal/occlude). Reveal/occlude are used eg if the object is on
		// a tab of a tabbox that is currently not selected. Show/hide is used to
		// hide controls that shall not be seen at the moment.

		/**
		 * Can the widget be seen by the user?
		 * \returns whether or not the widget can be seen.
		 */
		bool isExposed(void);

		/**
		 * Flags the Widget as visible.
		 */
		virtual void show(void);

		/**
		 * Flags the Widget as invisible.
		 */
		virtual void hide(void);

		/**
		 * Returns the Widget's visible flag.
		 * The Widget can still be invisible if it's occluded. For determining whether the Widget is actually visible on the screen, use isExposed.
		 */
		bool isVisible(void) { return _visible; }

		/**
		 * Flags the Widget as occluded. Only call this when implementing a Widget can manages occlusions, like a TabBox.
		 */
		virtual void occlude(void);

		/**
         * Flags the Widget as not occluded. Only call this when implementing a Widget can manages occlusions, like a TabBox.
         */
		virtual void reveal(void);

		/**
		 * Returns the Widget's occluded flag.
		 * The Widget can still be invisible if it's flagged as invisible. For determining whether the Widget is actually visible on the screen, use isExposed.
		 */
		bool isOccluded(void) { return _occluded; }

		/**
		 * Change the size of the Widget
		 * \param w the new width
		 * \param h the new height
		 */
		void resize(u16 w, u16 h);

		/**
		 * Flag the Widget as enabled so it's drawn like an enabled Widget and accepts input.
		 */
		virtual void enable(void);

		/**
		 * Flag the Widget as disabled so it's drawn like a disabled Widget and does not accept input.
		 */
		virtual void disable(void);

		/**
		 * Get the Widget's enabled flag.
		 */
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
		virtual void penUp() {};
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
