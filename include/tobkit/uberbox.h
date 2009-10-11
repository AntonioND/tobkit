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
 * uberbox.h
 *
 *  Created on: Nov 12, 2008
 *      Author: tob
 */

#ifndef UBERBOX_H_
#define UBERBOX_H_

#include "widget.h"
#include "gui.h"
#include "label.h"
#include "button.h"
#include "checkbox.h"
#include "numberslider.h"
#include "radiobutton.h"

#include <string>
#include <vector>

using namespace std;

//
// A generic dialog box.
//
// Usage:
//   - Add a bunch of widgets
//   - add the response buttons
//   - register the callback
//   - show the box
//   - in the callback, read out values
//
// Widgets will be shown in the box in the order they are entered, except for buttons which will always be on the bottom
//

class UberBox: public Widget {
	public:
		UberBox(u16 **vram_, const string &message_);
		~UberBox(void);

		// Event calls
		void penDown(u8 x_, u8 y_);
		void penUp(u8 x_, u8 y_);

		void show(void);
		void reveal(void);
		void setTheme(Theme *theme_, u16 bgcolor_);

		void registerButtonCallback(void (*callback_)(void));

		// Add controls
		void addRadioButton(const string &text_, bool on_=true);
		void newRadioGroup(void); // After calling this, new radiobuttons will be assicoated to a new group
		void addCheckBox(const string &text_, bool on_=true);
		void addNumberSlider(const string &text_, int min_=0, int max_=255, int value_=0, bool hex_=false, int step_=1);
		void addButton(const string &text_);

		// Read Values
		const string &getResult(void); // Returns the text of the button that was pressed
		const string &getRadioOption(int idx_); // idx_ is the index of the radio group
		const bool getChecked(int idx_);
		const int getNumber(int idx_);

	private:
		GUI gui;
		string msg;
		void (*callback)(void);

		vector<RadioButton::RadioButtonGroup*> radiobuttongroups;
		vector<RadioButton*> radiobuttons;
		vector<CheckBox*> checkboxes;
		vector<NumberSlider*> NumberSliders;
		vector<Button*> Buttons;
};

#endif /* UBERBOX_H_ */
