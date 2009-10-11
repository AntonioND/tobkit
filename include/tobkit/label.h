#ifndef LABEL_H
#define LABEL_H

#include "tobkit/widget.h"

namespace TobKit
{

class Label: public Widget {

	public:
	    Label(WidgetManager *owner, const string &caption, int x, int y,
	            bool has_border=false, int width=-1, int height=-1,
	            bool visible=true);

		~Label(void);

		// Drawing request
		void pleaseDraw(void);

		// Event calls
		void penDown(u8 x, u8 y);

		void setCaption(const string &caption);
		const string &getCaption(void);

		// Signals
		sigc::signal<void> signal_pushed;

	private:
	    void draw(void);

		string _caption;
		bool _has_border;
};

};

#endif
