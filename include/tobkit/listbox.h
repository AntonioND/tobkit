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

/**
 * \brief An editable, scrollable list of strings.
 *
 * \image html listbox.png
 *
 */
class ListBox: public Widget, public WidgetManager {

    public:
        /**
         * Creates a ListBox
         * \param owner the GUI that the Widget belongs to
         * \param x x-position on the screen
         * \param y y-position on the screen
         * \param n_items initial number of items
         * \param width in pixels
         * \param height <b>in lines(!)</b> The height in pixels will be height * ROW_HEIGHT + 1
         * \param show_numbers show numbers in front of the items
         * \param hex show numbers as hexadecimal values
         * \param start_with_zero if true, the numbering starts with 0, else with 1
         * \param visible if the Widget is drawn and responds to input
         */
        ListBox(WidgetManager *owner, int x, int y, int n_items = 0, int width = 130,
                int height = 10, bool show_numbers = false, bool hex = false, bool start_with_zero = true,
                bool visible = true);

        /**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penDown(int x, int y);

        /**
         * The pen is moved on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penMove(int x, int y);

        /**
         * The pen is lifted from the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penUp();

        // Add / delete /set /get elements

        /**
         * Add an item to the end of the list.
         * \param name the name of the item
         */
        void add(const string &name);

        /**
         * Delete an item
         * \param item The index of the item. If omitted, will delete the currently selected item.
         */
        void del(int item = -1);

        /**
         * Insert an item at a certain position.
         * \param name the name of the item to be inserted
         * \param idx the index of the item after which to insert the new item. If omitted, the new item will be inserted after the selected item.
         */
        void insert(const string &name, int idx=-1);

        /**
         * Sets the name of an item
         * \param idx the index of the item to change
         * \param name the new name of the item
         */
        void set(int idx, const string &name);

        /**
         * Get an item from the list.
         * \param the index of the item to get. If omitted, will return the currently selected item.
         * \returns the name of the item
         */
        const string get(int idx=-1);

        /**
         * Get the index of the selected element.
         * \returns the index, or -1 if no item is selected
         */
        int getidx(void);

        /**
         * Clear the list.
         */
        void clear(void);

        /**
         * Select an element
         * \param idx The index of the item to select.
         */
        void select(int idx);

        /**
         * This signal is emitted if the selection is changed. It passes the index of the new selection.
         */
        sigc::signal<void, int> signal_changed;

    protected:
        void draw(void);
        void scrollPosChanged(int idx);

        static const int ROW_HEIGHT = 11;
        static const int COUNTER_WIDTH = 17;

        ScrollThingy *_scrollthingy;

        enum InputState {
                NONE, LIST, SCROLLTHINGY
        };
        InputState _input_state;
        int _active_element;
        bool _show_numbers, _zero_offset, _hex; // zero_offset: If false, offset=1
        int _pixel_offset, _pen_pos_on_list;
        std::vector<std::string> _elements;
        bool _scrolled; // Whether the user has scrolled during the current interaction
};

}
;

#endif
