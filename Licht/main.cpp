#include <Windows.h> // Windows API
#include "Graphics.h"
#include "Sprite.h"
#include <string>
#include <wchar.h>

int windowClientWidth = 1920;
int windowClientHeight = 1080;

Graphics* graphics;

/*  WINAPI means _stdcall, it's a standard Windows Function
	HINSTANCE is a handle to the instance of your app. It's used to register and create our window.
		In the background, it's an identifying pointer
	LPSTR is char*, it's a regular ascii, null terminated, 8 bit character string
	LPWSTR is WCHAR*, or wchar_t*. It is a 16 bit Unicode string.
	
	hInstance: This is an ID for our application which the OS uses to load some resources, such as 
		windows, icons and bitmaps.
	hPrevInstance: Always NULL nowadays, it was used in 16 bit programs as a handle to an already
		running instance of the app. You wouldn't have to re-register your classes and you'd have
		access to the window and resources of the already executing app.
	pCmdLine: Command line arguments. This is the only difference between wWinMain and WinMain.
		WinMain uses 8 bit char* and wWinMain uses "wide" 16 bit unicode characters.
	pCmdShow: This parameter allows our window to begin with certain states, like SW_MAXIMIZED,
		SW_MINIMIZED. We can set the state to whatever we like, but this parameter allows Windows
		to pass a requested beginning state.

	For a more thorough description of the WinMain and wWinMain entry point procedures, look at the
	appropriate MSDN pages.
*/

// function used to process events that occur in the window (messages sent to the window)
// hwnd (handle to our window), uMsg (event message that occurs), xParam (additional parameters)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	if (uMsg == WM_PAINT) {
		graphics->BeginDraw();
		Sprite* windowBorder1 = new Sprite(L"D:/dev/Licht/sprites/windowBorder1.png", graphics);
		windowBorder1->Draw(1.0f, 0.0f, 0.0f);
		graphics->DrawBorderFade2C(18.0f, 4.0f, 28.0f, 72.0f, 3.0f, 19.5f, 52.5f, 2.0f, 11.0f, 33.0f, 1920.0f, 1080.0f, 34.0f, 70.0f, true, false);
		graphics->EndDraw();
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam); // Passes the Msg on for Windows to handle it (default)
}

// Main Entry Point of this Windows Application Program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowClass {};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	// windowClass.style = CS_HREDRAW | CS_VREDRAW; // Redraw when window is resized horizontally & vertically

	RegisterClassEx(&windowClass);

	// Adjust rect (800x600 pixels) to include the pixels of the window's borders when the window is created
	// This makes the non-border pixels of the window 800x600, without including the border's pixels
	RECT rect = { 0, 0, windowClientWidth, windowClientHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Licht", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	
	if (!windowHandle) return -1;

	graphics = new Graphics();
	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);
	
	// Main Message (Event) Loop
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		// Endlessly Listen for Messages (Events)
		DispatchMessage(&message);
	}

	delete graphics;

	return 0;
}