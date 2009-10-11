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
        void penUp(int x, int y);
        void penMove(int x, int y);

        void setScrollPosition(int position);
        int getScrollPosition();

        void setNElements(int n);

        // Signals
        sigc::signal<void, int> signal_changed;

        static const int WIDTH = 7;
        static const int MIN_SCROLLTHINGY_SIZE = 5;

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
