#ifndef BUTTON_H
#define BUTTON_H

#include "tobkit/widget.h"

#include <string>

using namespace std;

namespace TobKit
{

/** \brief The Button, the most basic of Widgets. Humble, yet powerful. Behold it's amazing powers!
 *
 */
class Button: public Widget
{
    public:
        /**
         * Creates a Button
         * \param owner the GUI that the Button belongs to
         * \param caption the text on the Button
         * \param x x-position on the screen
         * \param y y-position on the screen
         * \param screen the screen that the Button is on
         * \param width width of the Button
         * \param height height of the Button
         * \param listening_buttons hardware buttons that activate the Button, ORed together, e.g. KEY_A | KEY_B
         * \param visible if the button is drawn and responds to input
         */
        Button(WidgetManager *owner, const string &caption, int x, int y,
                int width=-1, int height=-1,
                u16 listening_buttons=0, bool visible=true);

        ~Button();

        /**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penDown(int x, int y);

        /**
         * The pen is lifted from the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void penUp(int x, int y);

        /**
         * A (hardware) button that the (software) Button reacts to is pressed.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
        void buttonPress(u16 button);

        /*
         * Change the Button's caption
         */
        void setCaption(const string &caption);

        /**
         * This signal is emitted if the Button is pushed.
         */
        sigc::signal<void> signal_pushed;

    private:
        void draw(void);

        bool _pen_is_down;
        string _caption;
};

};

#endif
