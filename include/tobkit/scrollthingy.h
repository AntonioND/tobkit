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

/*
 * scrollthingy.h
 *
 *  Created on: Feb 8, 2009
 *      Author: tob
 */

#ifndef SCROLLTHINGY_H_
#define SCROLLTHINGY_H_

#include "tobkit/widget.h"

namespace TobKit
{

class ScrollThingy: public TobKit::Widget {
    public:
        ScrollThingy(WidgetManager *owner, int x, int y, int size, int n_elements, int n_elements_visible,
                bool horizontal=false, bool visible=true);
        virtual ~ScrollThingy();

        // Event calls
        void penDown(int x, int y);
        void penUp();
        void penMove(int x, int y);

        void setScrollPosition(int position);
        int getScrollPosition();

        void setNElements(int n);
        int getNElements();

        // Signals
        sigc::signal<void, int> signal_changed;

        static const int WIDTH = 7;
        static const int MIN_SCROLLTHINGY_SIZE = 15;

    private:
        // Calculate height and position of the scroll thingy
        void calcScrollThingy(void);
        void setScrollThingyPos(int scrollthingy_pos);
        void draw(void);

        enum ButtonState {NONE, SCROLLUP, SCROLLDOWN, SCROLLTHINGY};
        ButtonState _buttonstate;
        int _scrollpos, _oldscrollpos;
        int _scrollthingy_pos, _scrollthingy_size, _pen_pos_on_scrollthingy;
        int _size, _n_elements, _n_elements_visible;
        bool _horizontal;
};

};

#endif /* SCROLLTHINGY_H_ */
