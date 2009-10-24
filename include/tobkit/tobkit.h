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

#ifndef TOBKIT_H_
#define TOBKIT_H_

/*! \mainpage Tobkit documentation
 *
 * \section intro_sec So you're actually reading the documentation
 *
 * Great idea! But reading documentations is boring compared to coding,
 * isn't it? If you would rather get your hands dirty with GUI code right away,
 * install Tobkit as described below and check out the example that
 * comes with the library. If you think learning by doing is for noobs,
 * there's a getting started guide just for you.
 *
 * \section install_sec Installation
 *
 *  Tobkit was developed using <b>devkitARM r26</b> and <b>libnds 1.3.8</b>. Make sure you have
 *  these versions or newer ones.
 *
 *  To install Tobkit, just copy
 *
 *   - <b>lib/libtobkit.a</b> and <b>lib/libsigc-2.0.a</b> to <b>libnds/lib</b>
 *   - <b>include/tobkit</b> and <b>include/sigc++</b> to <b>libnds/include</b>
 *
 *  and you're all set.
 *
 *  \section gettingstarted Getting started
 *
 *	\subsection adding Adding Tobkit to your project
 *
 *  To use Tobkit, edit your project's Makefile and add <b>-ltobkit -lsigc-2.0</b> to the
 *  <b>LIBS</b> variable. Make sure to put it <i>before -lnds9</i>! The definition should
 *  then look like this: \code LIBS	:= -ltobkit_new -lsigc-2.0 -lnds9 \endcode
 *
 *  Then, add \code #include <tobkit/tobkit.h> \endcode to your source code and code away!
 *
 *  \subsection init Initialising the screens
 *
 *  TODO
 *
 *  \subsection widgets Creating some widgets
 *
 *  \subsection mainloop Poking the GUI
 *
 *  \section more More Info
 *  - \ref interop
 *  - \ref icons
 */

/*! \page interop Integrating TobKit into your project
 *
 * This page explains how to integrate TobKit into applications that have graphics other than the TobKit GUI.
 * For example, you can use TobKit on one screen and use the other screen for other purposes, like displaying images of kittens.
 * You can also mix TobKit and other graphics on the same screen.
 *
 * \section sepscreen TobKit on a separate screen
 * No problem here. Just call GUI::setupVideoMain() or GUI::setupVideoSub() to setup TobKit on one screen and use the other screen for
 * whatever.
 *
 * \section samescreen TobKit and user-defined graphics on the same screen
 *
 * \subsection tile Tile based graphics
 *
 * Since TobKit has some tile-based Widgets, it has its own management for BG Layers, VRAM and palettes.
 * In order to use these resources for your own purposes without conflicts, you can implement your own Widget class and request the
 * resources you need from TobKit.
 *
 * TODO mehr erklaeren.
 * - Link auf: wie mach ich mein eigenes widget
 * - map and char mem allocation, palette allocation
 * - map and char reallocation callback
 *
 * \subsection bmp Bitmap graphics
 *
 * If you just want to draw your own bitmap graphics, you can implement your own Widget and let TobKit handle the rest. If you want to
 * have bitmap graphics on a separate background layer (for example for scrolling), you can the VRAM and background
 * initialization functions of libnds.
 * However, in order to avoid resource conflicts, you have to follow some rules:
 * - Have the graphics on a separate background layer and VRAM bank. Please refer to the documentation of GUI::setupVideoMain() or
 * GUI::setupVideoSub() for info on what graphics mode, VRAM banks and backgrounds TobKit uses.
 * - If you use a paletted bitmap, get the palette from TobKit using GUI::addPalette().
 *
 * \subsection threed 3D graphics
 * TODO
 *
 */

/*! \page icons Making monochrome icons for Buttons and TabViews
 *
 * In order to create a TobKit::BitButton or a TobKit::TabView, you need icons! TobKit uses bit-packed monochrome icons, which means
 * that every bit represents one Pixel which can be either black or white.
 *
 * \section makeicon Creating the icon
 * Just fire up your favorite graphics editor and make a new RGB image of the desired size.
 * Check the documentation of the respective Widgets for the default sizes. Draw the icon using only black and white. White pixels will
 * be made transparent by TobKit. Save the icon as a plain RGB image,
 * i.e. an image with no header, just alternating RGB values. If your image editor does not support this format, save the image as
 * png and use ImageMagick's convert tool like this:
 * \code
 * convert my_icon.png my_icon.rgb
 * \endcode
 *
 * \section convicon Converting the icon
 * In the <b>tools</b> folder of TobKit, you will find the tool rgb2bin, which converts rgb images to the correct format. Call it like this:
 * \code
 * ./rgb2bin my_icon.rgb
 * \endcode
 * This will create the file my_icon.bin.
 *
 * \section useicon Using the icon
 * Copy the icon to the <b>data</b> folder of your project. If this folder does not exist, create it and make sure that the DATA variable
 * in the Makefile points to it. Then, in the source, add:
 * \code
 * #include "my_icon_bin.h"
 * \endcode
 *
 * You can then create a BitButton like this:
 * \code
 * BitButton *bb = new BitButton(&gui, my_icon_bin, 50, 50);
 * \endcode
 */

#include <tobkit/gui.h>

#include <tobkit/bitbutton.h>
#include <tobkit/button.h>
#include <tobkit/scrollthingy.h>
//#include <tobkit/checkbox.h>
//#include <tobkit/fileselector.h>
//#include <tobkit/fontchars.h>
//#include <tobkit/groupbox.h>
//#include <tobkit/htabbox.h>
//#include <tobkit/keyb_hit.h>
#include <tobkit/keyboard.h>
//#include <tobkit/keyboard.map.h>
//#include <tobkit/keyboard.pal.h>
//#include <tobkit/keyboard.raw.h>
//#include <tobkit/label.h>
#include <tobkit/listbox.h>
//#include <tobkit/memoryindicator.h>
//#include <tobkit/messagebox.h>
//#include <tobkit/numberbox.h>
//#include <tobkit/numberslider.h>
//#include <tobkit/pixmap.h>
//#include <tobkit/radiobutton.h>
//#include <tobkit/tabbox.h>

//#include <tobkit/togglebutton.h>
#include <tobkit/typewriter.h>
//#include <tobkit/typewriter.hit.h>
//#include <tobkit/typewriter.map.h>
//#include <tobkit/typewriter.pal.h>
//#include <tobkit/typewriter.raw.h>

#endif /* CONSTANTS_H_ */
