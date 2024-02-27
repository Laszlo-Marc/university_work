#include <crtdbg.h>
#include "UI.h"
#include "AllTests.h"

void run() {
	testAll::testAbsolutelyEverything();
	//UI ui{};
	//ui.Start();
}

int main() {
	run();
	_CrtDumpMemoryLeaks();

	return 0;

}