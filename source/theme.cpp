#include "tobkit/theme.h"

Theme::Theme(void)
{
	// Set default colors
	col_bg                  = RGB15(4,6,15)|BIT(15);
	col_dark_bg             = col_bg;
	col_medium_bg           = RGB15(9,11,17)|BIT(15);
	col_light_bg            = RGB15(16,18,24)|BIT(15);
	col_lighter_bg          = RGB15(23,25,31) | BIT(15);
	col_light_ctrl          = RGB15(31,31,0)|BIT(15); // RGB15(26,26,26)|BIT(15)
	col_dark_ctrl           = RGB15(31,18,0)|BIT(15); // RGB15(31,31,31)|BIT(15)
	col_light_ctrl_disabled = col_light_bg;
	col_dark_ctrl_disabled  = col_medium_bg;
	col_list_highlight1     = RGB15(28,15,0)|BIT(15);
	col_list_highlight2     = RGB15(28,28,0)|BIT(15);
	col_outline             = RGB15(0,0,0)|BIT(15);
	col_sepline             = RGB15(31,31,0)|BIT(15);
	col_icon                = RGB15(0,0,0)|BIT(15);
	col_text                = RGB15(0,0,0)|BIT(15);
	col_signal              = RGB15(31,0,0)|BIT(15);

	precalcGradients();
}

void Theme::precalcGradients(void)
{
		/*
		// this is the old code that did this
		u8 r1,g1,b1,r2,g2,b2,rn,gn,bn;
		r1 = col1 & 0x001F;
		g1 = (col1 >> 5) & 0x001F;
		b1 = (col1 >> 10) & 0x001F;
		r2 = col2 & 0x001F;
		g2 = (col2 >> 5) & 0x001F;
		b2 = (col2 >> 10) & 0x001F;
		rn = r1*alpha/255 + r2-r2*alpha/255;
		gn = g1*alpha/255 + g2-g2*alpha/255;
		bn = b1*alpha/255 + b2-b2*alpha/255;
		return RGB15(rn,gn,bn)|BIT(15);
		*/

		gradient_ctrl.resize(256);
		u16 col1 = col_dark_ctrl; u16 col2 = col_light_ctrl;

		for(u16 alpha=0;alpha<256; ++alpha) {
			// This is the above code in 1 Line (faster)
			gradient_ctrl[alpha] = RGB15((col1 & 0x001F)*alpha/255 + (col2 & 0x001F)-(col2 & 0x001F)*alpha/255,
				     ((col1 >> 5) & 0x001F)*alpha/255 + ((col2 >> 5) & 0x001F)-((col2 >> 5) & 0x001F)*alpha/255,
				     ((col1 >> 10) & 0x001F)*alpha/255 + ((col2 >> 10) & 0x001F)-((col2 >> 10) & 0x001F)*alpha/255
				     )|BIT(15);
		}

		gradient_ctrl_disabled.resize(256);
		col1 = col_dark_ctrl_disabled; col2 = col_light_ctrl_disabled;

		for(u16 alpha=0;alpha<256; ++alpha) {
			// This is the above code in 1 Line (faster)
			gradient_ctrl_disabled[alpha] = RGB15((col1 & 0x001F)*alpha/255 + (col2 & 0x001F)-(col2 & 0x001F)*alpha/255,
				     ((col1 >> 5) & 0x001F)*alpha/255 + ((col2 >> 5) & 0x001F)-((col2 >> 5) & 0x001F)*alpha/255,
				     ((col1 >> 10) & 0x001F)*alpha/255 + ((col2 >> 10) & 0x001F)-((col2 >> 10) & 0x001F)*alpha/255
				     )|BIT(15);
		}

		gradient_bg.resize(256);
		col1 = col_medium_bg; col2 = col_light_bg;
		for(u16 alpha=0;alpha<256; ++alpha) {
                // This is the above code in 1 Line (faster)
                gradient_bg[alpha] = RGB15((col1 & 0x001F)*alpha/255 + (col2 & 0x001F)-(col2 & 0x001F)*alpha/255,
                         ((col1 >> 5) & 0x001F)*alpha/255 + ((col2 >> 5) & 0x001F)-((col2 >> 5) & 0x001F)*alpha/255,
                         ((col1 >> 10) & 0x001F)*alpha/255 + ((col2 >> 10) & 0x001F)-((col2 >> 10) & 0x001F)*alpha/255
                         )|BIT(15);
            }
}
