#include "MainScreen.h"

void MainScreen::Load()
{
}

void MainScreen::Unload()
{
}

void MainScreen::Render(Graphics* graphics)
{
	graphics->GetRenderTarget()->Clear(D2D1::ColorF(0.25f, 0.25f, 0.25f));
}

void MainScreen::Update()
{
}