#include "Controller.h"
#include "Graphics.h"

bool Controller::loading;
std::list<Screen*> Controller::screens;

void Controller::Init()
{
	loading = true;
}

void Controller::Release()
{
	loading = true;
	for (Screen* screen : screens)
	{
		screen->Unload();
		delete screen;
	}
}

void Controller::LoadScreen(Screen* screen)
{
	loading = true;
	screens.push_back(screen);
	screen->Load();
	loading = false;
}

void Controller::UnloadScreen(Screen* screen)
{
	loading = true;
	screens.remove(screen);
	screen->Unload();
	delete screen;
	loading = false;
}

void Controller::Render(Graphics* graphics)
{
	if (loading) return;
	
	for (Screen* screen : screens)
	{
		if (screen)
			screen->Render(graphics);
	}
}

void Controller::Update()
{
	for (Screen* screen : screens)
	{
		if (screen)
			screen->Update();
	}
}