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

#ifndef TOBKIT_TOGGLEBITBUTTON_H
#define TOBKIT_TOGGLEBITBUTTON_H

#include "tobkit/widget.h"
#include "tobkit/togglebutton.h"

namespace TobKit
{

    /**
     * A button with a small bitmap on it that is toggled on and off, like a switch.
     * \image html togglebitbutton.png
     */
    class ToggleBitButton: public ToggleButton
    {
        public:
            /**
             * Creates a ToggleBitButton
             * \param owner the GUI that the Button belongs to
             * \param bitmap the image on the Button
             * \param x x-position on the screen.
             * \param y y-position on the screen
             * \param width width of the Button
             * \param height height of the Button
             * \param bmpwidth width of the bitmap in pixels
             * \param bmpheight height of the bitmap in pixels
             * \param bmpx x-position of the bitmap on the Button
             * \param bmpy y-position of the bitmap on the Button
             * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
             * \param visible if the button is drawn and responds to input
             */
            ToggleBitButton(WidgetManager *owner, const u8 *bitmap, int x, int y,
                            int width=17, int height=17, int bmpwidth=13,
                            int bmpheight=13, int bmpx=2, int bmpy=2,
                            u16 listening_buttons=0, bool visible=true);

        private:
            void draw(void);

            const u8 *_bitmap;
            int _bmpwidth, _bmpheight, _bmpx, _bmpy;
    };

}

#endif /* TOBKIT_TOGGLEBITBUTTON_H */
