#include "tobkit/listbox.h"

#include <stdlib.h>
#include <stdio.h>

#include "tobkit/tools.h"

namespace TobKit {

/* ===================== PUBLIC ===================== */

ListBox::ListBox(WidgetManager *owner, int x, int y, int n_items, int width, int height, bool show_numbers, bool zero_offset, bool visible) :
    Widget(x, y, width, height, owner, visible), WidgetManager(*owner, Widget::_theme->col_bg, Widget::_theme->col_text), _input_state(NONE),
            _active_element(0), _show_numbers(show_numbers), _zero_offset(zero_offset), _pixel_offset(0) {
    _scrollthingy = new ScrollThingy(this, _x + width - ScrollThingy::WIDTH, _y, height, n_items, roundUpDiv(height, ROW_HEIGHT), false);
    for (int i = 0; i < n_items; ++i) {
        _elements.push_back("");
    }
    pleaseDraw();
}

// Event calls
void ListBox::penDown(int x, int y) {
    int relx = x - _x, rely = y - _y;

    if (relx < _width - ScrollThingy::WIDTH) {
        _input_state = LIST;
        _pen_pos_on_list = rely;
        // Item select
        /*
         u16 rel_item_clicked;
         rel_item_clicked = rely / ROW_HEIGHT;
         u16 newactiveelement = rel_item_clicked + scrollpos;
         if((newactiveelement != activeelement)&&(newactiveelement<elements.size())) {
         activeelement = newactiveelement;
         if(onChange != 0) {
         onChange(activeelement);
         }

         draw();
         }
         */
    } else {
        WidgetManager::penDown(x, y);
        _input_state = SCROLLTHINGY;
        /*
         // Scroll
         if(py<y+SCROLLBUTTON_HEIGHT) {
         buttonstate=SCROLLUP;
         if(scrollpos>0) {
         scrollpos--;
         calcScrollThingy();
         draw();
         }
         } else if(py>y+height-SCROLLBUTTON_HEIGHT) {
         buttonstate=SCROLLDOWN;
         s16 max_scollpos = elements.size()-height/ROW_HEIGHT;
         if(max_scollpos<0) max_scollpos=0;
         if(scrollpos<max_scollpos) {
         scrollpos++;
         calcScrollThingy();
         draw();
         }
         } else if((py>y+SCROLLBUTTON_HEIGHT+scrollthingypos)&&(py<y+SCROLLBUTTON_HEIGHT+scrollthingypos+scrollthingyheight)) {
         // The scroll thingy
         buttonstate=SCROLLTHINGY;
         pen_y_on_scrollthingy = py - (y+SCROLLBUTTON_HEIGHT+scrollthingypos);
         draw();
         } else if((py>y+SCROLLBUTTON_HEIGHT)&&(py<y+SCROLLBUTTON_HEIGHT+scrollthingypos)) {
         // Above the scroll thingy
         u16 rows_displayed = (height-1)/ROW_HEIGHT;
         if(scrollpos>rows_displayed) {
         scrollpos -= rows_displayed;
         } else {
         scrollpos = 0;
         }
         calcScrollThingy();
         draw();
         } else if((py>y+SCROLLBUTTON_HEIGHT+scrollthingypos+scrollthingyheight)&&(py<y+height-SCROLLBUTTON_HEIGHT)) {
         // Below the scroll thingy
         u16 rows_displayed = (height-1)/ROW_HEIGHT;
         s16 max_scollpos = elements.size()-height/ROW_HEIGHT;
         if(scrollpos+rows_displayed<max_scollpos) {
         scrollpos += rows_displayed;
         } else {
         scrollpos = max_scollpos;
         }
         calcScrollThingy();
         draw();
         }
         */
    }
}

void ListBox::penUp(int x, int y) {
    _input_state = NONE;
    WidgetManager::penUp(x, y);
    int py = y - _y;
}

void ListBox::penMove(int x, int y) {
    if (_input_state == SCROLLTHINGY) {
        WidgetManager::penMove(x, y);
        /*
         // So this is what GUI code looks like .. Ugh!
         s16 new_pen_y_on_scrollthingy = py - (y+SCROLLBUTTON_HEIGHT+scrollthingypos);
         s16 new_scrollthingypos = scrollthingypos + new_pen_y_on_scrollthingy - pen_y_on_scrollthingy;
         if(new_scrollthingypos < 0) new_scrollthingypos = 0;
         scrollthingypos = new_scrollthingypos;
         u16 max_scrollthingypos = height-2*SCROLLBUTTON_HEIGHT-scrollthingyheight+2;
         if(scrollthingypos > max_scrollthingypos) {
         scrollthingypos = max_scrollthingypos;
         }

         // Calculate new scroll position
         s16 max_scrollpos = elements.size()-height/ROW_HEIGHT;
         if(max_scrollpos<0) max_scrollpos = 0;
         if(max_scrollthingypos == 0) {
         scrollpos = 0;
         } else {
         scrollpos = scrollthingypos * max_scrollpos / max_scrollthingypos;
         }

         //iprintf("scrollthingy: %u\nscroll: %u\nmaxscroll: %d\n",scrollthingypos,scrollpos,max_scrollpos);
         if(scrollpos != oldscrollpos) {
         // Snap scrollthingy position
         scrollthingypos = scrollpos * max_scrollthingypos/ max_scrollpos;
         draw();
         oldscrollpos = scrollpos;
         }
         */
    } else if (_input_state == LIST) {
        int py = y - _y;
        int pen_diff = py - _pen_pos_on_list;
        _pen_pos_on_list = py;
        _pixel_offset -= pen_diff;
        _pixel_offset = clamp(_pixel_offset, 0, ROW_HEIGHT * _elements.size() - _height);
        int new_scrollpos = _pixel_offset / ROW_HEIGHT;
        _scrollthingy->setScrollPosition(new_scrollpos);
        pleaseDraw();
    }
}

// Add / delete elements
void ListBox::add(const string &name) {
    _elements.push_back(name);
    pleaseDraw();
}

// Always deletes selected item
void ListBox::del(void) {
    /*
     if(elements.size() > 0) {
     elements.erase(elements.begin() + activeelement);

     // Move activeelemnt up if the last active element was deleted
     if(activeelement > elements.size()-1) {
     activeelement = elements.size()-1;
     }

     // If an element from the bottom of the list was deleted so that
     // the last row is empty, scroll up if possible
     if(scrollpos>elements.size()-height/ROW_HEIGHT) {
     scrollpos = elements.size()-height/ROW_HEIGHT;
     }

     if(activeelement >= scrollpos) {
     pleaseDraw();
     }
     }
     */
}

// Inserts an element at position idx
void ListBox::insert(int idx, const string &name) {
    _elements.insert(_elements.begin() + idx, name);

    pleaseDraw();
}

void ListBox::set(int idx, const string &name) {
    _elements.at(idx) = name;

    if ((idx >= _scrollthingy->getScrollPosition()) && (idx < _scrollthingy->getScrollPosition() + (_height - 1) / ROW_HEIGHT)) {
        draw();
    }
}

const string &ListBox::get(int idx) {
    return _elements.at(idx);
}

int ListBox::getidx(void) {
    return _active_element;
}

void ListBox::clear(void) {
    _active_element = 0;
    _scrollthingy->setNElements(0);
    _elements.clear();
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

    int rows_displayed = (_height - 1) / ROW_HEIGHT;
    int row_pixel_offset = _pixel_offset % ROW_HEIGHT;

    // Fill rows
    for (int i = 0; i <= rows_displayed; ++i) {
        std::vector<u16> *grad;
        int grad_start_y, grad_height;
        if(i==0) {
            grad_start_y = 1;
            grad_height = ROW_HEIGHT - 1 - row_pixel_offset;
        } else if(i==rows_displayed) {
            grad_start_y = ROW_HEIGHT * i + 1 - row_pixel_offset;
            grad_height = row_pixel_offset;
        } else {
            grad_start_y = ROW_HEIGHT * i + 1 - row_pixel_offset;
            grad_height = ROW_HEIGHT - 1;
        }
        if (_scrollthingy->getScrollPosition() + i == _active_element) {
            grad = &Widget::_theme->gradient_ctrl;
        } else {
            grad = &Widget::_theme->gradient_bg;
        }
        drawGradient(*grad, 1, grad_start_y, _width - ScrollThingy::WIDTH - 1, grad_height);
    }

    // Horizontal Separator Lines
    for (int i = 0; i <= rows_displayed - 1; ++i) {
        drawHLine(1, ROW_HEIGHT * (i + 1) - row_pixel_offset, _width - ScrollThingy::WIDTH - 1, Widget::_theme->col_sepline);
    }
    /*
     // Vertical number separator line
     if(show_numbers) {
     drawLine(COUNTER_WIDTH,1,height-2,0,theme->col_sepline);
     }

     // Scrollbar
     // Upper Button
     if(buttonstate==SCROLLUP) {
     drawGradient(theme->col_dark_ctrl, theme->col_light_ctrl, width-SCROLLBAR_WIDTH+1, 1, 8, 8);
     } else {
     drawGradient(theme->col_light_ctrl, theme->col_dark_ctrl, width-SCROLLBAR_WIDTH+1, 1, 8, 8);
     }

     // This draws the up-arrow
     s8 j, p;
     for(j=0;j<3;j++) {
     for(p=-j;p<=j;++p) {
     *(*vram+SCREEN_WIDTH*(y+j+3)+x+width-SCROLLBAR_WIDTH+4+p) = RGB15(0,0,0) | BIT(15);
     }
     }

     drawBox(width-SCROLLBAR_WIDTH, 0, 9, 9);

     // Lower Button
     if(buttonstate==SCROLLDOWN) {
     drawGradient(theme->col_dark_ctrl, theme->col_light_ctrl, width-SCROLLBAR_WIDTH+1, height-9, 8, 8);
     } else {
     drawGradient(theme->col_light_ctrl, theme->col_dark_ctrl, width-SCROLLBAR_WIDTH+1, height-9, 8, 8);
     }

     // This draws the down-arrow
     for(j=2;j>=0;j--) {
     for(p=-j;p<=j;++p) {
     *(*vram+SCREEN_WIDTH*(y-j+height-4)+x+width-SCROLLBAR_WIDTH+4+p) = RGB15(0,0,0) | BIT(15);
     }
     }

     drawBox(width-SCROLLBAR_WIDTH, height-9, 9, 9);

     drawBox(width-SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH,height);

     // Clear Scrollbar
     drawGradient(theme->col_medium_bg, theme->col_light_bg, width-SCROLLBAR_WIDTH+1, SCROLLBUTTON_HEIGHT, SCROLLBAR_WIDTH-2, height-2*SCROLLBUTTON_HEIGHT);

     // The scroll thingy
     if(buttonstate==SCROLLTHINGY) {
     drawFullBox(width-SCROLLBAR_WIDTH+1, SCROLLBUTTON_HEIGHT-1+scrollthingypos, SCROLLBAR_WIDTH-2, scrollthingyheight, theme->col_list_highlight2);
     } else {
     drawFullBox(width-SCROLLBAR_WIDTH+1, SCROLLBUTTON_HEIGHT-1+scrollthingypos, SCROLLBAR_WIDTH-2, scrollthingyheight, theme->col_list_highlight1);
     }
     drawBox(width-SCROLLBAR_WIDTH, SCROLLBUTTON_HEIGHT+scrollthingypos-1, SCROLLBAR_WIDTH, scrollthingyheight);

     // Numbers (if enabled)
     u16 contentoffset;
     if(show_numbers) {
     char *numberstr = (char*)malloc(4);
     //iprintf("%u %u\n",scrollpos,elements.size());
     u16 offset;
     if(zero_offset==true) {
     offset=0;
     } else {
     offset=1;
     }
     for(i=0;(i<height/ROW_HEIGHT)&&(scrollpos+i<elements.size());++i) {
     sprintf(numberstr,"%2x",scrollpos+i+offset);
     drawString(numberstr, 2, ROW_HEIGHT*i+2);
     }
     free(numberstr);

     contentoffset = COUNTER_WIDTH;
     } else {
     contentoffset = 0;
     }
*/
     // Content
     for(int i = 0; (i < _height / ROW_HEIGHT) && (_scrollthingy->getScrollPosition() + i < _elements.size()); ++i) {
         drawString(_elements.at(_scrollthingy->getScrollPosition() + i).c_str(), /*contentoffset*/ + 2, ROW_HEIGHT * i + 2, _width /*- contentoffset*/ - 2 - ScrollThingy::WIDTH - 2);
     }

    drawBorder();
}

/*
 // Calculate height and position of the scroll thingy
 void ListBox::calcScrollThingy(void)
 {

 if(elements.size() < height/ROW_HEIGHT)
 scrollthingyheight = height-2*SCROLLBUTTON_HEIGHT+2;
 else
 scrollthingyheight = (height-2*SCROLLBUTTON_HEIGHT+2) * (height/ROW_HEIGHT)/elements.size();

 if(scrollthingyheight > height-2*SCROLLBUTTON_HEIGHT+2)
 scrollthingyheight = height-2*SCROLLBUTTON_HEIGHT+2;

 if(scrollthingyheight < MIN_SCROLLTHINGYHEIGHT)
 scrollthingyheight = MIN_SCROLLTHINGYHEIGHT;

 s16 max_scrollpos = elements.size()-height/ROW_HEIGHT;
 if(max_scrollpos < 0)
 max_scrollpos = 0;

 u16 max_scrollthingypos = height-2*SCROLLBUTTON_HEIGHT-scrollthingyheight+2;
 if(max_scrollpos == 0)
 scrollthingypos = 0;
 else
 scrollthingypos = max_scrollthingypos * scrollpos/max_scrollpos;
 }
 */
}
;
