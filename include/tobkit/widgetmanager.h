/*
 * widgetmanager.h
 *
 *  Created on: Feb 21, 2009
 *      Author: tob
 */

#ifndef WIDGETMANAGER_H_
#define WIDGETMANAGER_H_

#include <tobkit/constants.h>
#include <tobkit/theme.h>
#include <tobkit/widget.h>

#include <vector>

namespace TobKit {

class GUI;
class Widget;

class WidgetManager {
    friend class Widget;

    public:
        WidgetManager(Screen screen, GUI *gui, Theme theme);

        // This constructor is used to override bg_color and text_color. This is necessary for Widgets that
        // subclass a WidgetManager, but have a background color different from the theme's background color.
        WidgetManager(Screen screen, GUI *gui, Theme theme, u16 bg_color, u16 text_color);

        WidgetManager(WidgetManager &widgetmanager, u16 bg_color, u16 text_color);

        virtual ~WidgetManager();

        // Input handler - call this every vblank
        void handleInput(u16 keysdown, u16 keysup, u16 keysheld, touchPosition touch);

         // Input events. The user shouldn't use these except if he wants to fake pen events
        void penDown(int x, int y);
        void penUp(int x, int y); // Remove the coordinates here!
        void penMove(int x, int y);
        void buttonPress(u16 buttons);
        void buttonRelease(u16 buttons);

    protected:
        void draw(void);

        // Show/Hide all elements
        void showAll(void);
        void hideAll(void);

        void occludeAll(void);
        void revealAll(void);

        // Adds a widget and specifies which hardware buttons it listens to
        void addWidget(Widget *w, u16 listeningButtons = 0);

        // Removes a widget from the GUI
        void removeWidget(Widget *w);

        // Registers a widget that is in top of all other widgets and has input
        // priority, like a popup-window
        void setOverlayWidget(Widget *w);

        // Remove the overlay widget
        void removeOverlayWidget();

        // Find the widget that got hit
        Widget *getWidgetAt(int x, int y);
        Widget *getWidgetForButtons(u16 buttons);

        Screen _screen;
        GUI *_gui;
        Theme *_theme;
        u16 _bg_color, _text_color;
        u16 last_pen_x, last_pen_y;
        std::vector<Widget*> _widgets;
        std::vector<Widget*> _shortcuts;
        Widget *_active_widget;
        Widget *_overlay_widget;
};

};

#endif /* WIDGETMANAGER_H_ */
