/*
 * tools.h
 *
 *  Created on: Nov 16, 2008
 *      Author: tob
 */

#ifndef TOOLS_H_
#define TOOLS_H_

namespace TobKit
{
#define	abs(x)	        (x<0?(-x):(x))
};

inline s32 clamp(s32 x, s32 m, s32 M) {
    return max(m, min(M, x));
}

// Returns the upper Gauss bracket of the quotient of two integers x and y
inline s32 roundUpDiv(s32 x, s32 y) {
    return (x + (y - 1)) / y;
}

#endif /* TOOLS_H_ */
