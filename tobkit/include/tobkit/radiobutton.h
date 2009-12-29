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

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "tobkit/widget.h"

#include <stdio.h>
#include <vector>

namespace TobKit {

/** \brief Lets the user chose one of several alternative options.
 * RadioButtons that show alternative choices members of the same RadioButtonGroup.
 * \image html radiobutton.png
 */
class RadioButton: public Widget {
	public:

        /** \brief The RadioButtonGroup makes sure that only one of the RadioButtons in it is selected at the same time.
         * Listen to the RadioButtonGroup's change signal to know when the selected RadioButton changes.
         */
		class RadioButtonGroup {
			public:
                /**
                 * Creates a RadioButtonGroup
                 */
				RadioButtonGroup();
				
				/**
				 * Add a RadioButton to the group.
				 * \param rb the RadioButton to be added
				 */
				void add(RadioButton *rb);

				/**
				 * Sets a RadioButton as checked (by its pointer).
				 * \param rb the RadioButton to be checked.
				 */
				void setChecked(RadioButton *rb);

				/**
                 * Sets a RadioButton as checked (by its index, in the order the RadioButtons were added).
                 * \param rb the index of the RadioButton to be checked.
                 */
				void setChecked(int idx);
	
				/**
				 * Get the index of the checked RadioButton (in the order they were added).
				 * \return the index of the checked RadioButton.
				 */
				int getChecked();

				sigc::signal<void, int> signal_changed;

			private:
				std::vector<RadioButton*> _rbvec;
		};
		
        /**
         * Creates a RadioButton. Before you do that, make a RadioButtonGroup that the RadioButton should belong to.
         * \param owner the GUI that the Button belongs to
         * \param caption the text on he RadioButton
         * \param x x-position on the screen.
         * \param y y-position on the screen
         * \param rgb the RadioButtonGroup that the RadioButton should belong to
         * \param width how many pixels it's wide. -1 means choose automatically.
         * \param height how many pixels it's high. -1 means choose automatically.
         * \param visible if the Widget is drawn and responds to input
         */
		RadioButton(WidgetManager *owner, string caption, int x, int y,
				RadioButtonGroup *rbg, int width=-1, int height=-1, bool visible=true);
		
		/**
         * The pen is put down on the Widget.
         * This method is called by the GUI.
         * You only need this method if you want to simulate the event manually.
         */
		void penDown(int x, int y);
		
		/**
		 * Change the caption
         * \param caption the new caption.
		 */
		void setCaption(const string &caption);
		
	private:
		/**
		 * Set the RadioButton to checked or unchecked
		 * \param active true if you want it checked, else false
		 */
		void setChecked(bool active);

		void draw(void);
	
		RadioButtonGroup *_rbg;
		bool _active;
		string _label;
};

};

#endif
