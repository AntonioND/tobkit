#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "tobkit/widget.h"

#include <nds.h>

namespace TobKit
{

class Keyboard: public Widget {

    public:
        Keyboard(WidgetManager *owner, int x, int y, bool visible=true);
        ~Keyboard();

        // Set up the keyboard graphics using a tiled background
        void setupPalette(void);
        void setupTileBg(void);

        // Event calls
        void penDown(int x, int y);
        void penUp(int x, int y);

        // Key label handling
        void showKeyLabels(void);
        void hideKeyLabels(void);
        void setKeyLabel(u8 key, char label);

        // Signals
        sigc::signal<void, u8> signal_note;
        sigc::signal<void, u8> signal_release;

    private:
        u16 *_char_base, *_map_base;
        int _palette_normal_index, _palette_fullnotehighlight_index, _palette_halfnotehighlight_index;

        void draw(void);
        void setKeyPal(u8 note);
        bool isHalfTone(u8 note);
        void resetPals(void);

        void drawKeyLabel(u8 key, bool visible=true);
        void eraseKeyLabel(u8 key);

        char _key_labels[24];
        bool _key_labels_visible;
        u16 _curr_note;
};

};

#endif
