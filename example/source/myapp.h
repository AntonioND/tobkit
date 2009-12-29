/*
 * myapp.h
 *
 *  Created on: Nov 16, 2008
 *      Author: tob
 *
 *  This is your application's main class.
 *  You do not have to use a class for the application.
 *  You can as well implement all the functionality in the main() function,
 *  but I think it's cleaner this way.
 */

#ifndef MYAPP_H_
#define MYAPP_H_

#include <tobkit/tobkit.h>
#include <nds.h>

using namespace TobKit;

class MyApp {
public:
	MyApp();
	virtual ~MyApp();

	void mainLoop(void);

private:
	void sayHello(void);
	void handleTypewriterOk(void);
	void handleTypewriterCancel(void);
	void note(u8 note);

	void delkb1();
	void addkb1();
	void delkb2();
	void addkb2();

	void scrollThingyChanged(int pos);
	void showKB();
	void twOK();
	void del();
	void ins();

    void flipText(bool on);

	GUI *gui_main, *gui_sub;
	TobKit::Keyboard *kb;
	TobKit::Typewriter *tw;
	TobKit::Label *label;
	ListBox *listbox;
	GroupBox *groupbox;

	RadioButton::RadioButtonGroup *rbg;
    RadioButton *rb1, *rb2, *rb3;
};

#endif /* MYAPP_H_ */
