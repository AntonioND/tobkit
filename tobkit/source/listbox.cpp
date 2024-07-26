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

#include <stdlib.h>
#include <stdio.h>

#include "tobkit/listbox.h"
#include "tobkit/tools.h"

namespace TobKit {

/* ===================== PUBLIC ===================== */

ListBox::ListBox(WidgetManager *owner, int x, int y, int n_items, int width, int height, bool show_numbers, bool hex, bool zero_offset, bool visible) :
    Widget(x, y, width, height * ROW_HEIGHT + 1, owner, visible), WidgetManager(*owner, Widget::_theme->col_bg, Widget::_theme->col_text), _input_state(NONE),
            _active_element(-1), _show_numbers(show_numbers), _zero_offset(zero_offset), _hex(hex), _pixel_offset(0), _scrolled(false) {

    _scrollthingy = new ScrollThingy(this, _x + width - ScrollThingy::WIDTH, _y, _height, n_items, height, false);
    _scrollthingy->signal_changed.connect(sigc::mem_fun(this, &ListBox::scrollPosChanged));

    for (int i = 0; i < n_items; ++i) {
        _elements.push_back("");
    }
    pleaseDraw();
}

// Event calls
void ListBox::penDown(int x, int y) {
    int relx = x - _x, rely = y - _y;
    _scrolled = false;

    if (relx < _width - ScrollThingy::WIDTH) {
        _input_state = LIST;
        _pen_pos_on_list = rely;
    } else {
        WidgetManager::penDown(x, y);
        _input_state = SCROLLTHINGY;
    }
}

void ListBox::penUp() {
    // Item select
    if( (_input_state == LIST) && (!_scrolled) ) {
        u16 rel_item_clicked;
        rel_item_clicked = _pen_pos_on_list / ROW_HEIGHT;
        u16 newactiveelement = rel_item_clicked + _scrollthingy->getScrollPosition();
        if( (newactiveelement != _active_element) && (newactiveelement < _elements.size()) ) {
            _active_element = newactiveelement;
            signal_changed(_active_element);
            draw();
        }
    }

    _input_state = NONE;
    WidgetManager::penUp();
}

void ListBox::penMove(int x, int y) {
    if (_input_state == SCROLLTHINGY) {
        WidgetManager::penMove(x, y);
    } else if (_input_state == LIST) {
        int py = y - _y;
        int pen_diff = py - _pen_pos_on_list;
        _pen_pos_on_list = py;
        _pixel_offset -= pen_diff;
        _pixel_offset = clamp(_pixel_offset, 0, ROW_HEIGHT * _elements.size() - _height + 1);
        int new_scrollpos = _pixel_offset / ROW_HEIGHT;
        if(_scrollthingy->getScrollPosition() != new_scrollpos) {
            _scrollthingy->setScrollPosition(new_scrollpos);
            _scrolled = true;
        }
        pleaseDraw();
    }
}

// Add / delete elements
void ListBox::add(const string &name) {
    _elements.push_back(name);
    _scrollthingy->setNElements(_scrollthingy->getNElements() + 1);
    pleaseDraw();
}

// Deletes an item
void ListBox::del(int item) {
    if(item < 0) {
        if(_active_element < 0) {
            return;
        } else {
            item = _active_element;
        }
    }
    if(_elements.size() > 0) {
        _elements.erase(_elements.begin() + item);
        _scrollthingy->setNElements(_scrollthingy->getNElements() - 1);

        // Move active elemnt up if the last active element was deleted
        if(_active_element > (int)_elements.size() - 1) {
            _active_element = _elements.size() - 1;
        }

        // If an element from the bottom of the list was deleted so that
        // the last row is empty, scroll up if possible
        if(_scrollthingy->getScrollPosition() > (int)_elements.size() - _height / ROW_HEIGHT) {
            _scrollthingy->setScrollPosition(_elements.size() - _height / ROW_HEIGHT);
        }

        if( (_active_element >= _scrollthingy->getScrollPosition()) || (_elements.size() == 0) ) {
            pleaseDraw();
        }
    }
}

// Inserts an element at position idx
void ListBox::insert(const string &name, int idx) {
    if(idx == -1) {
        if(_active_element == -1) {
            return;
        } else {
            idx = _active_element;
        }
    }
    _elements.insert(_elements.begin() + idx + 1, name);
    _scrollthingy->setNElements(_scrollthingy->getNElements() + 1);

    pleaseDraw();
}

void ListBox::set(int idx, const string &name) {
    _elements.at(idx) = name;

    if ((idx >= _scrollthingy->getScrollPosition()) && (idx < _scrollthingy->getScrollPosition() + (_height - 1) / ROW_HEIGHT)) {
        draw();
    }
}

const string ListBox::get(int idx) {
    if(idx == -1) {
        if(_active_element == -1) {
            return "";
        }
        idx = _active_element;
    } else if( (idx < 0) || (idx >= (int)_elements.size()) ) {
        return "";
    }
    return _elements.at(idx);
}

int ListBox::getidx(void) {
    return _active_element;
}

void ListBox::clear(void) {
    _active_element = -1;
    _scrollthingy->setNElements(0);
    _elements.clear();
    _scrollthingy->setNElements(0);
    pleaseDraw();
}

void ListBox::select(int idx) {
    _active_element = idx;

    // Scroll down if activeelement is under the viewport
    if (_scrollthingy->getScrollPosition() + _height / ROW_HEIGHT - 1 < _active_element) {
        _scrollthingy->setScrollPosition(_active_element - _height / ROW_HEIGHT + 1);
    }

    // Scroll up if activeelement is above the viewport
    if (_scrollthingy->getScrollPosition() > _active_element) {
        _scrollthingy->setScrollPosition(_active_element);
    }

    pleaseDraw();
}

/* ===================== PRIVATE ===================== */

void ListBox::draw(void) {
    if (!isExposed())
        return;

    WidgetManager::draw();

    int scrollpos = _scrollthingy->getScrollPosition();
    int rows_displayed = _height / ROW_HEIGHT;
    int row_pixel_offset = _pixel_offset % ROW_HEIGHT;

    // Fill rows
    for (int i = 0; i <= rows_displayed; ++i) {
        std::vector<u16> *grad;
        int grad_start_y, grad_height;
        if(i == 0) {
            grad_start_y = 1;
            grad_height = ROW_HEIGHT - 1 - row_pixel_offset;
        } else if(i==rows_displayed) {
            grad_start_y = ROW_HEIGHT * i + 1 - row_pixel_offset;
            grad_height = row_pixel_offset;
        } else {
            grad_start_y = ROW_HEIGHT * i + 1 - row_pixel_offset;
            grad_height = ROW_HEIGHT - 1;
        }
        if (scrollpos + i == _active_element) {
            grad = &Widget::_theme->gradient_ctrl;
        } else {
            grad = &Widget::_theme->gradient_bg;
        }
        drawGradient(*grad, 1, grad_start_y, _width - ScrollThingy::WIDTH - 1, grad_height);
    }

    // Horizontal Separator Lines
    int n_lines = (row_pixel_offset == 0) ? (rows_displayed - 1) : (rows_displayed);

    for (int i = 0; i < n_lines; ++i) {
        drawHLine(1, ROW_HEIGHT * (i + 1) - row_pixel_offset, _width - ScrollThingy::WIDTH - 1, Widget::_theme->col_sepline);
    }

    u16 contentoffset = 0;
    if(_show_numbers) {
        // Vertical number separator line
        drawVLine(COUNTER_WIDTH, 1, _height - 2, Widget::_theme->col_sepline);

        char *numberstr = (char*)malloc(4);
        u16 offset = _zero_offset ? 0 : 1;

        for(int i = 0; (i < _height / ROW_HEIGHT + 1) && (scrollpos + i < (int)_elements.size()); ++i) {
            if(_hex) {
                sprintf(numberstr, "%2x", scrollpos + i + offset);
            } else {
                sprintf(numberstr, "%2d", scrollpos + i + offset);
            }
            drawString(numberstr, 2, ROW_HEIGHT * i + 2 - row_pixel_offset);
        }
        free(numberstr);

        contentoffset = COUNTER_WIDTH;
    }

     // Content
     for(unsigned int i = 0; (i < (unsigned int)(_height / ROW_HEIGHT + 1)) && (scrollpos + i < (unsigned int)_elements.size()); ++i) {
         drawString(_elements.at(_scrollthingy->getScrollPosition() + i).c_str(), contentoffset + 2, ROW_HEIGHT * i + 2 - row_pixel_offset, _width - contentoffset - 2 - ScrollThingy::WIDTH - 2);
     }

    drawBorder();
}

void ListBox::scrollPosChanged(int idx)
{
    _pixel_offset = idx * ROW_HEIGHT;
    pleaseDraw();
}

};
