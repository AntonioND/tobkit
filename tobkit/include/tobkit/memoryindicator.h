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

#ifndef MEMORYINDICATOR_H_
#define MEMORYINDICATOR_H_

#include "widget.h"

namespace TobKit
{

class MemoryIndicator : public Widget
{
	public:
		MemoryIndicator(u8 _x, u8 _y, u8 _width, u8 _height, u16 **_vram, bool _visible=true);
		~MemoryIndicator();
	
	// Drawing request
	void pleaseDraw(void);
			
	private:
		void draw(void);
		u32 getFreeMem(void);
		
		u32 total_ram;
};

};

#endif /*MEMORYINDICATOR_H_*/
