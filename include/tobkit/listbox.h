#ifndef LISTBOX_H
#define LISTBOX_H

#include <nds.h>
#include <vector>
#include <string>
#include "tobkit/widget.h"
#include "tobkit/scrollthingy.h"
/*
namespace TobKit {

class ListBox: public Widget {
	public:
	    ListBox(GUI *owner, int x, int y, Screen screen=SUB_SCREEN, int width=130,
	            int height=100, bool show_numbers, bool zero_offset=true, bool visible=true);

		// Event calls
		void penDown(int x, int y);
        void penUp(int x, int y);
        void buttonPress(u16 button);

		// Add / delete /set /get elements
		void add(const char *name);
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


		ScrollThingy *_scrollthingy;

		int _activeelement;

		bool _show_numbers, _zero_offset; // zero_offset: If false, offset=1
		std::vector<std::string> _elements;
};

};
*/
#endif
