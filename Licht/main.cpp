#include <Windows.h> // Windows API
#include <string>
#include <iostream>

#include "Graphics.h"
#include "Sprite.h"
#include "Controller.h"
#include "MainScreen.h"
#include "ApplicationScreen.h"

const int DEFAULT_CLIENT_WIDTH = 1920;
const int DEFAULT_CLIENT_HEIGHT = 1080;

// Function used to process messages sent to the window
LRESULT CALLBACK WindowProc(HWND windowHandle, UINT eventMessage, WPARAM wParam, LPARAM lParam)
{
	if (eventMessage == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(windowHandle, eventMessage, wParam, lParam); // Passes the Msg on for Windows to handle it (default)
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
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // Redraw when window is resized horizontally & vertically

	RegisterClassEx(&windowClass);

	// Adjust rect to include the pixels of the window's borders when the window is created
	RECT rect = { 0, 0, DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Licht2D", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowHandle) return -1;

	Graphics* graphics = new Graphics();
	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);

	D2D1_RECT_F applicationArea = D2D1::RectF(
		(DEFAULT_CLIENT_WIDTH - 1280) / 2, (DEFAULT_CLIENT_HEIGHT - 720) / 2, DEFAULT_CLIENT_WIDTH - (DEFAULT_CLIENT_WIDTH - 1280) / 2, DEFAULT_CLIENT_HEIGHT - (DEFAULT_CLIENT_HEIGHT - 720) / 2
	);

	Screen* mainScreen = new MainScreen();
	Screen* applicationScreen = new ApplicationScreen(applicationArea);

	Controller::Init();
	Controller::LoadScreen(mainScreen);
	Controller::LoadScreen(applicationScreen);

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		// Dispatching messages in the same thread as the update and render code can lead to performance issues and unresponsiveness
		if (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			Controller::Update();

			graphics->BeginDraw();
			Controller::Render(graphics);
			graphics->EndDraw();
		}
	}

	Controller::Release();
	delete graphics;
	return 0;
}