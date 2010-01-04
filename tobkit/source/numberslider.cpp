#include <cstdlib>
#include <cstdio>

#include "tobkit/numberslider.h"
#include "tobkit/fontchars.h"
#include "tobkit/tools.h"

#include "numberslider_doublearrow_raw.h"

namespace TobKit {

/* ===================== PUBLIC ===================== */

NumberSlider::NumberSlider(WidgetManager *owner, int x, int y, int value, int min,
                int max, bool hex, int width, bool visible)
    :Widget(x, y, width, 17, owner, 0, visible),
    _value(value), _btnstate(0), _min(min), _max(max), _hex(hex)
{
    char minstr[16], maxstr[16];
    if(_hex) {
        sprintf(minstr, "%x", min);
        sprintf(maxstr, "%x", max);
    } else {
        sprintf(minstr, "%d", min);
        sprintf(maxstr, "%d", max);
    }
    int n_places = MAX(strlen(minstr), strlen(maxstr));

    char printfstr_c[10];
    sprintf(printfstr_c, "%%%d%s", n_places, _hex ? "X" : "d");
    _printfstr = printfstr_c;

    if(width == -1) {
        _width = 11 + n_places * FONT_WIDTH;
    }

    pleaseDraw();
}

// Event calls
void NumberSlider::penDown(int px, int py)
{
	if((px>_x)&&(px<_x+32)&&(py>_y)&&(py<_y+17)) {
		_btnstate = true;
		_lasty = py;
	}
	
	if((px>_x)&&(px<_x+9)&&(py>_y)&&(py<_y+9)) {
		if(_value<_max)
		{
			_value++;
			signal_changed(_value);
		}
	} else if((px>_x)&&(px<_x+9)&&(py>_y+9)&&(py<_y+18)) {
		if(_value>_min)
		{
			_value--;
			signal_changed(_value);
		}
	}
	
	draw();
}

void NumberSlider::penUp()
{
	_btnstate = false;
	draw();
}

void NumberSlider::penMove(int px, int py)
{
	s16 dy = _lasty-py;
	if(abs(dy)>1) {
		int inc = dy*dy/8;
		if(inc == 0)
				inc = 1;
		if(dy < 0)
			inc = -inc;

		s16 newval = _value+inc;
			
		if(newval > _max) {
			_value=_max;
		} else if(newval<_min) {
			_value=_min;
		} else {
			_value=newval;
		}
		
		draw();
		
		signal_changed(_value);
		
		_lasty = py;
	}
}

void NumberSlider::setValue(int val)
{
	
	s32 oldval = _value;
	
	if(val > _max)
		_value = _max;
	else if (val < _min)
		_value = _min;
	else
		_value = val;
	
	if(oldval != _value)
	{
		signal_changed(_value);
		
		draw();
	}
	
}

int NumberSlider::getValue(void) {
	return _value;
}

/* ===================== PRIVATE ===================== */

void NumberSlider::draw(void)
{
	
	if(!isExposed())
		return;
	
	drawBorder();
	drawGradient(_theme->gradient_ctrl, 1, 1, 7, 15, !_btnstate);
	drawHLine(0, 8, 9, _theme->col_outline);
    drawMonochromeIcon(2, 3, 5, 11, numberslider_doublearrow_raw);
	drawVLine(8, 0, 17);
	drawFullBox(9, 1, _width - 10, 15, _theme->col_lighter_bg);

	char *numberstr = (char*)malloc(4);
	if(_hex==true) {
		sprintf(numberstr, _printfstr.c_str(), _value);
	} else {
		sprintf(numberstr, _printfstr.c_str(), _value);
	}
	drawString(std::string(numberstr), 10, 5);
	free(numberstr);
}

}
