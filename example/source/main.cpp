#include <nds.h>
#include "myapp.h"

MyApp *myapp;

int main(void)
{
	myapp = new MyApp();
	myapp->mainLoop();

	return 0;
}
