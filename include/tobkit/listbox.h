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

#ifndef LISTBOX_H
#define LISTBOX_H

#include <nds.h>
#include <vector>
#include <string>

#include "tobkit/widget.h"
#include "tobkit/scrollthingy.h"
#include "tobkit/widgetmanager.h"

namespace TobKit {

class ListBox: public Widget, public WidgetManager {
  public:
    ListBox(WidgetManager *owner, int x, int y, int n_items, int width = 130,
        int height = 100, bool show_numbers = false, bool zero_offset = true,
        bool visible = true);

    // Event calls
    void penDown(int x, int y);
    void penMove(int x, int y);
    void penUp(int x, int y);

    // Add / delete /set /get elements
    void add(const string &name);
    void del(void); // Deletes selected item
    void insert(int idx, const string &name);
    void set(int idx, const string &name); // Inserts an element at position idx
    const string &get(int idx);
    int getidx(void); // get index of selected element
    void clear(void);
    void select(int idx); // set selected element

    // Signals
    sigc::signal<int> signal_changed;

  protected:
    void draw(void);

    static const int ROW_HEIGHT = 11;
    static const int COUNTER_WIDTH = 17;

    ScrollThingy *_scrollthingy;

    enum InputState {
      NONE, LIST, SCROLLTHINGY
    };
    InputState _input_state;
    int _active_element;
    bool _show_numbers, _zero_offset; // zero_offset: If false, offset=1
    int _pixel_offset, _pen_pos_on_list;
    std::vector<std::string> _elements;
};

}
;

#endif
