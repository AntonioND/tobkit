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
 * scrollthingy.cpp
 *
 *  Created on: Feb 8, 2009
 *      Author: tob
 */

#include "tobkit/scrollthingy.h"
#include "tobkit/tools.h"

namespace TobKit
{

/* ===================== PUBLIC ===================== */

ScrollThingy::ScrollThingy(WidgetManager *owner, int x, int y, int size, int n_elements, int n_elements_visible, bool horizontal, bool visible)
    :Widget(x, y, horizontal?size:WIDTH, horizontal?WIDTH:size, owner, 0, visible),
    _scrollpos(0), _oldscrollpos(0), _pen_pos_on_scrollthingy(0),
    _size(size), _n_elements(n_elements), _n_elements_visible(n_elements_visible), _horizontal(horizontal)
{
    calcScrollThingy();
    pleaseDraw();
}

ScrollThingy::~ScrollThingy()
{

}

// Event calls
void ScrollThingy::penDown(int x, int y)
{
    int px = x - _x, py = y - _y;
    if(_horizontal) {
        if( (px >= _scrollthingy_pos) && (px <= _scrollthingy_pos + _scrollthingy_size) ) {
            _buttonstate = SCROLLTHINGY;
            _pen_pos_on_scrollthingy = px - _scrollthingy_pos;
            pleaseDraw();
        }
    } else {
        if( (py >= _scrollthingy_pos) && (py <= _scrollthingy_pos + _scrollthingy_size) ) {
            _buttonstate = SCROLLTHINGY;
            _pen_pos_on_scrollthingy = py - _scrollthingy_pos;
            pleaseDraw();
        }
    }
}

void ScrollThingy::penUp()
{
    _buttonstate = NONE;
    pleaseDraw();
}

void ScrollThingy::penMove(int x, int y)
{
    if(_buttonstate != SCROLLTHINGY) {
        return;
    }

    int px = x - _x, py = y - _y;
    int new_scrollthingy_pos;
    if(_horizontal) {
        new_scrollthingy_pos = px - _pen_pos_on_scrollthingy;
    } else {
        new_scrollthingy_pos = py - _pen_pos_on_scrollthingy;
    }
    new_scrollthingy_pos = clamp(new_scrollthingy_pos, 0, _size - _scrollthingy_size);
    setScrollThingyPos(new_scrollthingy_pos);
    pleaseDraw();
}

void ScrollThingy::setScrollPosition(int position)
{
    position = clamp(position, 0, _n_elements - _n_elements_visible);
    _scrollpos = position;
    calcScrollThingy();
    pleaseDraw();
}

int ScrollThingy::getScrollPosition()
{
    return _scrollpos;
}

void ScrollThingy::setNElements(int n)
{
    _n_elements = n;
    calcScrollThingy();
    pleaseDraw();
}

int ScrollThingy::getNElements()
{
    return _n_elements;
}

/* ===================== PRIVATE ===================== */

void ScrollThingy::calcScrollThingy(void)
{
    if(_n_elements <= _n_elements_visible) {
        _scrollthingy_pos = 0;
        _scrollthingy_size = _size;
    } else {
        _scrollthingy_size = min(_size * _n_elements_visible / _n_elements, _size);
        _scrollthingy_size = max(_scrollthingy_size, MIN_SCROLLTHINGY_SIZE);
        _scrollthingy_pos = min((_size - _scrollthingy_size) * _scrollpos / (_n_elements - _n_elements_visible), _size - _scrollthingy_size);
    }
}

void ScrollThingy::setScrollThingyPos(int scrollthingy_pos)
{
    int new_scrollpos;
    new_scrollpos = _scrollthingy_pos * (_n_elements - _n_elements_visible) / (_size - _scrollthingy_size);
    new_scrollpos = clamp(new_scrollpos, 0, _n_elements - _n_elements_visible);
    if(_scrollpos != new_scrollpos) {
        _scrollpos = new_scrollpos;
        signal_changed(new_scrollpos);
    }
    _scrollpos = new_scrollpos;
    _scrollthingy_pos = scrollthingy_pos;
}

void ScrollThingy::draw(void)
{
    drawGradient(_theme->gradient_bg, 1, 1, _width-2, _height-2, false);
    drawBorder();

    if(_horizontal) {
        drawGradient(_theme->gradient_ctrl, _scrollthingy_pos+1, 1, _scrollthingy_size-2, WIDTH-2, _buttonstate == SCROLLTHINGY);
        drawBox(_scrollthingy_pos, 0, _scrollthingy_size, WIDTH);
    } else {
        drawGradient(_theme->gradient_ctrl, 1, _scrollthingy_pos+1, WIDTH-2, _scrollthingy_size-2, _buttonstate == SCROLLTHINGY);
        drawBox(0, _scrollthingy_pos, WIDTH, _scrollthingy_size);
    }
}

};
