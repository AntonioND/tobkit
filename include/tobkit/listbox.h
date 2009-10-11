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
