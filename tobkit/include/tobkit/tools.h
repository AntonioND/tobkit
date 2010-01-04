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
 * tools.h
 *
 *  Created on: Nov 16, 2008
 *      Author: tob
 */

#ifndef TOBKIT_TOOLS_H
#define TOBKIT_TOOLS_H

namespace TobKit
{
#define	ABS(x)	    ((x)<0?(-x):(x))
#define MIN(x,y)    ((x)<(y)?(x):(y))
#define MAX(x,y)    ((x)>(y)?(x):(y))

inline s32 clamp(s32 x, s32 m, s32 M) {
    return max(m, min(M, x));
}

// Returns the upper Gauss bracket of the quotient of two integers x and y
inline s32 roundUpDiv(s32 x, s32 y) {
    return (x + (y - 1)) / y;
}

};

#endif /* TOOLS_H_ */
