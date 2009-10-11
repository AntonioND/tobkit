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

#ifndef BUTTON_H
#define BUTTON_H

#include "tobkit/widget.h"

#include <string>

using namespace std;

namespace TobKit
{

/** \brief The Button, the most basic of Widgets. Humble, yet powerful. Behold it's amazing powers!
 * \image html button.png
 */
class Button: public Widget
{
    public:
        /**
         * Creates a Button
         * \param owner the GUI that the Button belongs to
         * \param caption the text on the Button
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param width width of the Button
         * \param height height of the Button
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         * \param visible if the button is drawn and responds to input
         */
        Button(WidgetManager *owner, const string &caption, int x, int y,
                int width=-1, int height=-1,
                u16 listening_buttons=0, bool visible=true);

        ~Button();

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
        void penUp(int x, int y);

        /**
         * A (hardware) button that the (software) Button reacts to is pressed.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void buttonPress(u16 button);

        /*
         * Change the Button's caption
         */
        void setCaption(const string &caption);

        /**
         * This signal is emitted if the Button is pushed.
         */
        sigc::signal<void> signal_pushed;

    private:
        void draw(void);

        bool _pen_is_down;
        string _caption;
};

};

#endif
