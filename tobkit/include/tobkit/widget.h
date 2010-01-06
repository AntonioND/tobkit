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
		 * Flags the Widget as visible and draws it.
		 * When writing a Widget that contains other Widgets you should overload this function to show member Widgets recursively.
		 */
		virtual void show(void);

		/**
		 * Flags the Widget as invisible and eases it.
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
         * Flags the Widget as not occluded.
         * Only call this when implementing a Widget can manages occlusions, like a TabBox.
         * When writing a Widget that contains other Widgets you should overload this function to reveal member Widgets recursively.
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
		u16 _bgcolor; // Color of the background (for hiding the widget)
		u16 _textcolor; // Color of text (can be changed eg. if on a dark background)

		/**
		 * This is called to notify the widget that the pen was put down.
		 * Implement this function in your Widget.
		 * There is no sane reason to call this function yourself!
		 * \param px the x-position of the pen
		 * \param py the y-position of the pen
		 */
		virtual void penDown(int px, int py) {};

		/**
		 * This is called to notify the widget that the pen was lifted.
		 * Implement this function in your Widget.
		 * There is no sane reason to call this function yourself!
		 */
		virtual void penUp() {};

		/**
		 * This is called to notify the widget that the pen was moved.
         * Implement this function in your Widget.
         * There is no sane reason to call this function yourself!
         * \param px the x-position of the pen
         * \param py the y-position of the pen
		 */
		virtual void penMove(int px, int py) {};

		/**
		 * This is called to notify the widget that a hardware button was pressed.
		 * \param button the hardware button that was pressed (as defined in libnds)
		 */
		virtual void buttonPress(u16 button) {};

		/**
         * This is called to notify the widget that a hardware button was released.
         * \param button the hardware button that was released (as defined in libnds)
         */
		virtual void buttonRelease(u16 button) {};

		// Draw utility functions

		/**
		 * Draw text.
		 * \param str the string you want to draw
		 * \param tx the text's x-position
		 * \param ty the text's y-position
		 * \param maxwidth the maximum width of the text in pixels
		 * \param color the color of the text as an RGB15
		 * \sa \ref custom_font
		 */
		void drawString(const string &str, int tx, int ty, uint maxwidth=255, u16 color=RGB15(0,0,0)|BIT(15));

		/**
		 * Draw a rectangular box (outlined).
		 * \param tx x-coordinate of the upper left corner of the box
		 * \param ty y-coordinate of the upper left corner of the box
		 * \param tw width of the box
		 * \param th height of the box
		 * \param col the color of the box
		 */
		void drawBox(int tx, int ty, int tw, int th, u16 col=RGB15(0,0,0)|BIT(15));

		/**
		 * Draw a rectangular box (full).
		 * \param tx x-coordinate of the upper left corner of the box
         * \param ty y-coordinate of the upper left corner of the box
         * \param tw width of the box
         * \param th height of the box
         * \param col the color of the box
		 */
		void drawFullBox(int tx, int ty, int tw, int th, u16 col);

		/**
		 * Draw a box outlining the Widget's border
		 * \param col the color of the box
		 */
		void drawBorder(u16 col = RGB15(0,0,0)|BIT(15));

		/**
		 * Draw a horizontal line
		 * \param tx the x-coordinate of the left end of the line
		 * \param ty the y-coordinate of the left end of the line
		 * \param length the length of the line
		 * \param col the color of the line
		 */
		void drawHLine(int tx, int ty, int length, u16 col=RGB15(0,0,0)|BIT(15));

		/**
         * Draw a vertical line
         * \param tx the x-coordinate of the upper end of the line
         * \param ty the y-coordinate of the upper end of the line
         * \param length the length of the line
         * \param col the color of the line
         */
		void drawVLine(int tx, int ty, int length, u16 col=RGB15(0,0,0)|BIT(15));

		/**
		 * Draw a line of arbitrary direction
		 * \param tx1 the x-coordinate of the beginning of the line
		 * \param ty1 the y-coordinate of the beginning of the line
		 * \param tx2 the x-coordinate of the end of the line
		 * \param ty2 the y-coordinate of the end of the line
		 * \param the color of the line
		 */
		void drawLine(int tx1, int ty1, int tx2, int ty2, u16 col=RGB15(0,0,0)|BIT(15));

		/**
		 * Draws one pixel.
		 * \param tx the x-coordinate of the pixel
		 * \param ty the y-coordinate of the pixel
		 * \param col the color of the pixel
		 */
		void drawPixel(int tx, int ty, u16 col=RGB15(0,0,0)|BIT(15));

		/**
		 * Draws a color gradient.
		 * \param gradient a vector of RGB15 color values that make up the gradient. This is usually a member of a Theme.
		 * \param tx x-coordinate of the upper left corner of the gradient
		 * \param ty y-coordinate of the upper left corner of the gradient
		 * \param tw the width of the gradient
		 * \param th the height of the gradient
		 * \param reverse reverse the gradient
		 */
		void drawGradient(const std::vector<u16> &gradient, int tx, int ty, int tw, int th, bool reverse=false);

		/**
		 * Draws a monochrome icon. This is usually used for button-type Widgets.
		 * \sa \ref icons
		 * \param tx the x-coordinate of the upper left corner of the icon
		 * \param ty the y-coordinate of the upper left corner of the icon
		 * \param tw the width of the icon
		 * \param th the height of the icon
		 * \param icon a pointer to the icon
		 * \param color the color of the icon, default black
		 */
		void drawMonochromeIcon(int tx, int ty, int tw, int th, const u8 *icon, u16 color=RGB15(0,0,0)|BIT(15));

		// Stylus utility functions

		/**
		 * Check whether the pen is inside a rectangle. This is a utility function for widgets that have regions that do different things.
		 * If you use this, you probably should be using a sub-widget, but TobKit won't call the cops on you if you don't.
		 * \param x the x-position of the pen
		 * \param y the y-position of the pen
		 * \param x1 the x-coordinate of the upper left corner of the rectangle
		 * \param y1 the y-coordinate of the upper left corner of the rectangle
		 * \param x2 the x-coordinate of the lower right corner of the rectangle
		 * \param y2 the y-coordinate of the lower right corner of the rectangle
		 * \returns true if the pen is inside the rectangle, else false
		 */
		bool isInRect(int x, int y, int x1, int y1, int x2, int y2);

		/**
		 * How wide is the string when rendered?
		 * \param str the string
		 * \param limit If specified, the string is internally shortened to have a length less or equal to limit before calculating it's length.
		 */
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

        /**
         * Set up this Widget as an overlay Widget, i.e. a Widget that is on top of all other Widgets. Use this for dialog boxes, pop-up ads etc.
         */
        void setOverlay(void);

	private:
		bool _visible, _occluded;

		virtual void draw(void) = 0;

		// Overdraw the object with its background color when hiding it
		void overdraw(void);
};

};

#endif
