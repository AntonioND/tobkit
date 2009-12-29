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

#ifndef WIDGETMANAGER_H_
#define WIDGETMANAGER_H_

#include <tobkit/constants.h>
#include <tobkit/theme.h>
#include <tobkit/widget.h>

#include <vector>

namespace TobKit {

class GUI;
class Widget;

/**
 * \brief The manager. Always busy. Wearing a suit. Buying stocks on the cellphone. Manages Widgets in his spare time.
 *
 * This is a class that can contain Widgets. The GUI inherits from it, and so do all Widgets that contain sub-widgets.
 * It manages
 * \li \c Widget input (both via pen and hardware buttons)
 * \li \c Widget positions
 * \li \c Widget visibility (Widgets can be explicitly hidden or they can be occluded, e.g. in inactive TabBox tabs)
 * \li \c Widget drawing
 *
 * You only need to worry about this class if you want to implement a Widget that contains sub-Widgets.
 */
class WidgetManager {
    friend class Widget;

    public:
        /**
         * This constructor is used only by the GUI (which inherits from WidgetManager)
         * \param screen the screen all Widgets in this WidgetManager will appear on
         * \param gui a pointer to the GUI object
         * \param theme the Theme that all Widgets managed by this WidgetManager will have
         */
        WidgetManager(Screen screen, GUI *gui, Theme theme, bool dark_bg=true);

        /**
         * This constructor is used to override bg_color and text_color. This is necessary for Widgets that
         * subclass a WidgetManager, but have a background color different from the theme's background color.
         * \param screen the screen all Widgets in this WidgetManager will appear on
         * \param gui a pointer to the GUI object
         * \param theme the Theme that all Widgets managed by this WidgetManager will have
         * \param bg_color the background color of the widget that inherits WidgetManager
         * \param text_color the text color of the widget that inherits WidgetManager
         */
        WidgetManager(Screen screen, GUI *gui, Theme theme, u16 bg_color, u16 text_color);

        /**
         * This is the constructor you should use when creating a Widget that inherits from WidgetManager
         * \param widgetmanager the owning WidgetManager of your Widget
         * \param bg_color the background color of the widget that inherits WidgetManager
         * \param text_color the text color of the widget that inherits WidgetManager
         */
        WidgetManager(WidgetManager &widgetmanager, u16 bg_color, u16 text_color);

        virtual ~WidgetManager();

        /**
         * Handle the input from the user. This should be called every VBlank.
         * You only need this if you implement your own GUI.
         */
        void handleInput(u16 keysdown, u16 keysup, u16 keysheld, touchPosition touch);

         // Input events. The user shouldn't use these except if he wants to fake pen events

        /**
         * Tell that WidgetManager that the pen is put down.
         * You only need this method if you want to simulate the event manually.
         */
        void penDown(int x, int y);

        /**
         * Tell that WidgetManager that the pen is lifted.
         * You only need this method if you want to simulate the event manually.
         */
        void penUp();

        /**
         * Tell that WidgetManager that the pen is moved.
         * You only need this method if you want to simulate the event manually.
         */
        void penMove(int x, int y);

        /**
         * Tell that WidgetManager that a hardware button was pressed.
         * You only need this method if you want to simulate the event manually.
         */

        void buttonPress(u16 buttons);
        /**
         * Tell that WidgetManager that a hardware button was released.
         * You only need this method if you want to simulate the event manually.
         */
        void buttonRelease(u16 buttons);

        /**
         * Is the background on which Widgets are drawn dark (affects Widget color)
         * \return true if the background is dark, false if it is white
         */
        bool hasDarkBG() {return _dark_bg;}

    protected:
        /**
         * Draw all Widgets.
         */
        void draw(void);

        /**
         * Show all Widgets.
         */
        void showAll(void);

        /**
         * Hide all Widgets.
         */
        void hideAll(void);

        /**
         * Mark all Widgets as occluded.
         */
        void occludeAll(void);

        /**
         * Mark all Widgets as not occluded.
         */
        void revealAll(void);

        /**
         * Adds a widget and specifies which hardware buttons it listens to
         * \param w a pointer to the widget to add
         * \param listeningButtons the hardware buttons it listens to, ORed together
         */
        void addWidget(Widget *w, u16 listeningButtons = 0);

        /**
         * Removes a widget from the GUI
         * \param w the Widget to remove.
         */
        void removeWidget(Widget *w);

        /**
         * Registers a widget that is in top of all other widgets and has input priority, like a popup-window.
         * \param w the Widget that you want to make the overlay Widget.
         */
        void setOverlayWidget(Widget *w);

        /**
         * Remove the overlay widget
         */
        void removeOverlayWidget();

        /**
         * Find the widget that got hit by the pen
         * \param x the pen's x-coordinate.
         * \param y the pen's y-coordinate.
         * \returns the Widget that got hit, or NULL if no Widget got hit.
         */
        Widget *getWidgetAt(int x, int y);

        /**
         * Get the widget that listens to hardware buttons
         * \param The ORed together hardware buttons you want to check
         * \returns the Widget that listens to them. If there are multiple results, just one of them will be returned, so take care that your Widgets listen to different buttons.
         */
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
        bool _dark_bg;
};

};

#endif /* WIDGETMANAGER_H_ */
