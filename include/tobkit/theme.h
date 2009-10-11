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

#ifndef _THEME_H_
#define _THEME_H_

#include <nds.h>
#include <vector>

class Theme
{
	public:
		Theme();

		u16 col_bg;
		u16 col_dark_bg;
		u16 col_medium_bg;
		u16 col_light_bg;
		u16 col_lighter_bg;
		u16 col_light_ctrl;
		u16 col_dark_ctrl;
		u16 col_light_ctrl_disabled;
		u16 col_dark_ctrl_disabled;
		u16 col_list_highlight1;
		u16 col_list_highlight2;
		u16 col_outline;
		u16 col_sepline;
		u16 col_icon;
		u16 col_text;
		u16 col_signal;

		std::vector<u16> gradient_ctrl, gradient_ctrl_disabled, gradient_bg, gradient_bg_bright; // Precalculated gradients for quickly drawing nice buttons
	private:
		void precalcGradient(std::vector<u16> *gradient, const u16 col1, const u16 col2);
};

#endif
