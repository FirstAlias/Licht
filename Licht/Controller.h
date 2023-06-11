#pragma once
#include <list>
#include "Screen.h"

class Controller
{
	// private constructor, Singleton Class
	Controller() {}
	static std::list<Screen*> screens;
	static bool loading;
public:
	static void Init();
	static void Release();
	static void LoadScreen(Screen* screen);
	static void UnloadScreen(Screen* screen);
	static void Render(Graphics* graphics);
	static void Update();
};