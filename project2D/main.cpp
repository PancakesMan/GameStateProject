#include "Application2D.h"
#include <Windows.h>

int main() {
	
	// allocation
	auto app = new Application2D();

	// Get a handle to the console window
	HWND hwnd_win = GetForegroundWindow();

	// Hide the console window
	ShowWindow(hwnd_win, SW_HIDE);

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}