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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "tobkit/widget.h"

#include <nds.h>

namespace TobKit
{

class Keyboard: public Widget {

    public:
        Keyboard(WidgetManager *owner, int x, int y, bool visible=true);
        ~Keyboard();

        // Set up the keyboard graphics using a tiled background
        void setupPalette(void);
        void setupTileBg(void);

        // Event calls
        void penDown(int x, int y);
        void penUp(int x, int y);

        // Key label handling
        void showKeyLabels(void);
        void hideKeyLabels(void);
        void setKeyLabel(u8 key, char label);

        // Signals
        sigc::signal<void, u8> signal_note;
        sigc::signal<void, u8> signal_release;

    private:
        u16 *_char_base, *_map_base;
        int _palette_normal_index, _palette_fullnotehighlight_index, _palette_halfnotehighlight_index;

        void draw(void);
        void setKeyPal(u8 note);
        bool isHalfTone(u8 note);
        void resetPals(void);

        void drawKeyLabel(u8 key, bool visible=true);
        void eraseKeyLabel(u8 key);

        char _key_labels[24];
        bool _key_labels_visible;
        u16 _curr_note;
};

};

#endif
