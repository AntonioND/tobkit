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
 * widgetmanager.cpp
 *
 *  Created on: Feb 21, 2009
 *      Author: tob
 */

#include <algorithm>
#include <cstdio>

#include "tobkit/widgetmanager.h"
#include "tobkit/gui.h"

namespace TobKit {

/* ===================== PUBLIC ===================== */

WidgetManager::WidgetManager(Screen screen, GUI *gui, Theme theme)
    :_screen(screen), _theme(new Theme(theme)), _bg_color(theme.col_bg), _text_color(theme.col_text), _active_widget(0), _overlay_widget(0)
{

}

WidgetManager::WidgetManager(Screen screen, GUI *gui, Theme theme, u16 bg_color, u16 text_color)
    :_screen(screen), _theme(new Theme(theme)), _bg_color(bg_color), _text_color(text_color), _active_widget(0), _overlay_widget(0)
{

}

WidgetManager::WidgetManager(WidgetManager &widgetmanager, u16 bg_color, u16 text_color)
    :_screen(widgetmanager._screen), _gui(widgetmanager._gui), _theme(widgetmanager._theme),
    _bg_color(bg_color), _text_color(text_color), _active_widget(0), _overlay_widget(0)
{

}

WidgetManager::~WidgetManager() {
    // TODO Auto-generated destructor stub
}


void WidgetManager::handleInput(u16 keysdown, u16 keysup, u16 keysheld, touchPosition touch)
{
    if(keysdown & KEY_TOUCH) // PenDown
    {
        penDown(touch.px, touch.py);

        last_pen_x = touch.px;
        last_pen_y = touch.py;
    }

    if(keysup & KEY_TOUCH) // PenUp
    {
        penUp(touch.px, touch.py);
    }

    if( (keysheld & KEY_TOUCH) && ( (touch.px != last_pen_x) || (touch.py != last_pen_y) ) ) // PenMove
    {
        penMove(touch.px, touch.py);

        last_pen_x = touch.px;
        last_pen_y = touch.py;
    }

    if(keysdown & ~KEY_TOUCH)
    {
        buttonPress(keysdown);
    }

    if(keysup & ~KEY_TOUCH)
    {
        buttonRelease(keysdown);
    }
}


void WidgetManager::draw(void)
{
    std::vector<Widget*>::iterator w_it;

    for(w_it=_widgets.begin();w_it!=_widgets.end();++w_it)
    {
        if((*w_it)->isExposed()) {
            (*w_it)->pleaseDraw();
        }
    }

    if(_overlay_widget!=0) {
        _overlay_widget->pleaseDraw();
    }
}

void WidgetManager::penDown(int x, int y)
{
    Widget *w = getWidgetAt(x,y);

    if(w!=0) {
        _active_widget = w;
        w->penDown(x, y);
    }
}

void WidgetManager::penUp(int x, int y)
{
    if(_active_widget!=0) {
        if(_active_widget->isVisible()==true) {
            _active_widget->penUp(x, y);
            _active_widget = 0;
        }
    }
}

void WidgetManager::penMove(int x, int y)
{
    if(_active_widget!=0) {
        _active_widget->penMove(x, y);
    }
}

void WidgetManager::buttonPress(u16 buttons)
{
    Widget *w = getWidgetForButtons(buttons);
    if(w!=0) {
        if(w->isVisible()==true) {
            w->buttonPress(buttons);
        }
    }
}

void WidgetManager::buttonRelease(u16 buttons)
{
    Widget *w = getWidgetForButtons(buttons);
    if(w!=0) {
        if(w->isVisible()==true) {
            w->buttonRelease(buttons);
        }
    }
}

/* ===================== PRIVATE ===================== */

// Show/Hide all elements
void WidgetManager::showAll(void)
{
    for(std::vector<Widget*>::iterator w_it=_widgets.begin(); w_it!=_widgets.end(); ++w_it) {
        (*w_it)->show();
    }
}

void WidgetManager::hideAll(void)
{
    for(std::vector<Widget*>::reverse_iterator w_it=_widgets.rbegin(); w_it!=_widgets.rend(); ++w_it) {
        (*w_it)->hide();
    }
}

void WidgetManager::occludeAll(void)
{
    for(std::vector<Widget*>::reverse_iterator w_it=_widgets.rbegin(); w_it!=_widgets.rend(); ++w_it) {
        (*w_it)->occlude();
    }
}

void WidgetManager::revealAll(void)
{
    for(std::vector<Widget*>::iterator w_it=_widgets.begin(); w_it!=_widgets.end(); ++w_it) {
        (*w_it)->reveal();
    }
}

void WidgetManager::addWidget(Widget *w, u16 listeningButtons)
{
    _widgets.push_back(w);

    if(listeningButtons != 0) {
        for(int i=0;i<14;++i) {
            if(listeningButtons & BIT(i)) {
                _shortcuts[i] = w;
            }
        }
    }
}

void WidgetManager::removeWidget(Widget *w)
{
    if(_active_widget == w) {
        _active_widget = 0;
    }

    if(_overlay_widget == w) {
        removeOverlayWidget();
    }

    // Remove the widget from the WidgetManager
    std::vector<Widget*>::iterator wit = std::find(_widgets.begin(), _widgets.end(), w);
    if (*wit == w) {
        _widgets.erase(wit);
    } else {
        iprintf("Fatal error: Widget to be deleted not found!\n");
    }

    // Delete shortcuts associated with the widget
    for(wit = _shortcuts.begin();wit!=_shortcuts.end(); ++wit) {
        if(*wit == w) {
            *wit = 0;
        }
    }

    draw();
}

void WidgetManager::setOverlayWidget(Widget *w)
{
    _overlay_widget = w;
}

void WidgetManager::removeOverlayWidget()
{
    if(_active_widget==_overlay_widget) {
        _active_widget = 0;
    }
    _overlay_widget = 0;
    _gui->clearScreen();
}

Widget *WidgetManager::getWidgetAt(int x, int y) {

    int wx, wy, ww, wh;
    // Do we have an overlay?
    if(_overlay_widget != 0) {
        return _overlay_widget;
    }

    // Else follow the normal procedure
    bool found = false;
    std::vector<Widget*>::iterator w_it, end_it;

    w_it = _widgets.begin();
    end_it = _widgets.end();


    while((w_it!=end_it) && (!found)) {
        (*w_it)->getPos(&wx, &wy, &ww, &wh);

        if( (x > wx) && (x < wx + ww) && (y > wy) && (y < wy + wh) && ( (*w_it)->isExposed() == true) ) {
            found = true;
        } else {
            w_it++;
        }
    }

    if(!found) {
        return 0;
    } else {
        return *w_it;
    }
}

Widget *WidgetManager::getWidgetForButtons(u16 buttons) {

    if(_overlay_widget != 0) {
        return _overlay_widget;
    }

    Widget *w=0;
    u8 i;
    for(i=0;i<14;++i) {
        if(buttons & BIT(i)) {
            w = _shortcuts[i];
        }
    }
    return w;
}

};
