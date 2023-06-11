#include "ApplicationScreen.h"

ApplicationScreen::ApplicationScreen(D2D1_RECT_F initialApplicationScreenArea)
{
	occupiedAreaOnScreen = initialApplicationScreenArea;
}

void ApplicationScreen::Load()
{
}

void ApplicationScreen::Unload()
{
}

void ApplicationScreen::Render(Graphics* graphics)
{
	ID2D1SolidColorBrush* brush;
	graphics->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0.75f, 0.75f, 0.75f), &brush);
	graphics->GetRenderTarget()->FillRectangle(occupiedAreaOnScreen, brush);
}

void ApplicationScreen::Update()
{
}