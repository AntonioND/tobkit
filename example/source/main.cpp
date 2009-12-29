#include <nds.h>
#include "myapp.h"

MyApp *myapp;

int main(void)
{
	irqEnable(IRQ_VBLANK);

	myapp = new MyApp();
	myapp->mainLoop();

	return 0;
}
