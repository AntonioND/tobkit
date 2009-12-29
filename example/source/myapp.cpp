/*
 * myapp.cpp
 *
 *  Created on: Nov 16, 2008
 *      Author: tob
 */

#include "myapp.h"
#include <cstdio>

#include "bitbutton_circle_bin.h"

MyApp::MyApp()
{
	//
	// Set up the GUI
	//

	// Load and apply a theme (optional)
	//Theme theme("testtheme.tktheme");
	//tobkit.setTheme(theme);

	// Set up the screens:
	// - Top screen is double-buffered with console
	// - Bottom screen is single-buffered with two tiled backgrounds for keyboard and typewriter

	gui_main = GUI::instance(MAIN_SCREEN);//new GUI(MAIN_SCREEN);
	gui_sub = GUI::instance(SUB_SCREEN);
	gui_sub->setupConsole();

	lcdMainOnBottom();

    groupbox = new GroupBox(gui_main, "bla!", 2, 0, 70, 90);
    groupbox->setCaption("bla!"); // TODO: Without this line the widget is optimized away

	Button *button = new Button(gui_main, "Push me!", 110, 170);
	button->signal_pushed.connect(sigc::mem_fun(this, &MyApp::sayHello));

	listbox = new ListBox(gui_main, 50, 50, 0, 99, 8, true);

	Button *btn_add = new Button(gui_main, "add", 10, 10);
	Button *btn_del = new Button(gui_main, "Eel", 10, 30);
	Button *btn_clear = new Button(gui_main, "clear", 10, 50);
	Button *btn_ins = new Button(gui_main, "ins", 10, 70);

	Label *label = new Label(gui_main, "I'm a Label!", 50, 150, true);

	listbox->add("This");
	listbox->add("is");
	listbox->add("one");
	listbox->add("funky");
	listbox->add("ListBox!");

	btn_add->signal_pushed.connect(sigc::mem_fun(this, &MyApp::showKB));
	btn_del->signal_pushed.connect(sigc::mem_fun(this, &MyApp::del));
	btn_clear->signal_pushed.connect(sigc::mem_fun(listbox, &ListBox::clear));
	btn_ins->signal_pushed.connect(sigc::mem_fun(this, &MyApp::ins));

	BitButton *bb = new BitButton(gui_main, bitbutton_circle_bin, 50, 10);

	CheckBox *cb = new CheckBox(gui_main, "it's on", 150, 10);
	cb->signal_pushed.connect(sigc::mem_fun(this, &MyApp::flipText));

	rbg = new RadioButton::RadioButtonGroup();
	rbg->getChecked();
	rb1 = new RadioButton(gui_main, "mario", 170, 100, rbg);
	rb1->enable();
	rb2 = new RadioButton(gui_main, "luigi", 170, 120, rbg);
	rb3 = new RadioButton(gui_main, "waluigi", 170, 140, rbg);
}

MyApp::~MyApp() {
	// TODO Auto-generated destructor stub
}


void MyApp::mainLoop(void)
{
	// All input handling happens here.
	touchPosition touch;

	while(true) {
		scanKeys();
		touchRead(&touch);
		int down = keysDown();
		int held = keysHeld();
		int up = keysUp();

		gui_main->handleInput(down, up, held, touch);
		//gui.draw();
		swiWaitForVBlank();
		//gui.swapBuffers();
	}
}

void MyApp::sayHello(void)
{
    iprintf("Hello\n");
}

void MyApp::handleTypewriterOk(void)
{
	label->setCaption(tw->getText());
	delete tw;
}

void MyApp::handleTypewriterCancel(void)
{
	delete tw;
}

void MyApp::showKB()
{
    tw = new Typewriter(gui_main, "Gief!", "");
    tw->signal_ok.connect(sigc::mem_fun(this, &MyApp::twOK));
}

void MyApp::twOK()
{
    listbox->add(tw->getText());
    delete tw;
}

void MyApp::del()
{
    listbox->del();
}

void MyApp::ins()
{
    listbox->insert("FOLIBAA!!");
}

void MyApp::flipText(bool on)
{
    int idx = listbox->getidx();
    if(idx==-1) return;
    string name;
    if(on)
        name = "On";
    else
        name = "Off";
    listbox->set(idx, name);
}

