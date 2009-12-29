#include "tobkit/radiobutton.h"

namespace TobKit {

RadioButton::RadioButtonGroup::RadioButtonGroup()
{
}

void RadioButton::RadioButtonGroup::add(RadioButton *rb)
{
    // Check the 1st radiobutton only
    if(_rbvec.size() > 0) {
        rb->setChecked(false);
    } else {
        rb->setChecked(true);
    }
	_rbvec.push_back(rb);
}

void RadioButton::RadioButtonGroup::setChecked(RadioButton *rb)
{
	int counter = 0, pos = 0;
	std::vector<RadioButton*>::iterator rbit;
	
	// TODO: Replace this by find.
	for(rbit=_rbvec.begin(); rbit!=_rbvec.end(); ++rbit) {
		if(*rbit != rb) {
			(*rbit)->setChecked(false);
		} else {
			(*rbit)->setChecked(true);
			pos = counter;
		}
		counter++;
	}
	
	signal_changed(pos);
}

int RadioButton::RadioButtonGroup::getChecked()
{
    return 0; //TODO
}

void RadioButton::RadioButtonGroup::setChecked(int idx) {
	setChecked(_rbvec.at(idx));
}

}
