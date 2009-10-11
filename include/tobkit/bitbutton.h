#ifndef BITBUTTON_H
#define BITBUTTON_H

#include "tobkit/widget.h"

namespace TobKit
{

/**
 * \brief A Button with a monochrome icon on it.
 *
 * The default size for icons is 13x13 pixels. See below for instructions on how to make icons.
 * \sa \ref icons
 */
class BitButton: public Widget
{
	public:
	    BitButton(WidgetManager *owner, const u8 *bitmap, int x, int y, int width=17, int height=17,
	            u8 bmpwidth=13, u8 bmpheight=13, u8 bmpx=2, u8 bmpy=2, u16 listening_buttons=0, bool visible=true);

		// Drawing request
		void pleaseDraw(void);

		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void buttonPress(u16 button);

        // Signals
        sigc::signal<void> signal_pushed;

	private:
		void draw(void);

		bool _pen_is_down;
		const u8 *_bitmap;
		u8 _bmpwidth, _bmpheight, _bmpx, _bmpy;
};

};

#endif
