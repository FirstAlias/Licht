#pragma once
#include "Screen.h"

class ApplicationScreen : public Screen
{
	// This changes as the Engine User resizes the Central Application "Window" (via dragging the edges) -- Not Yet Implemented
	D2D1_RECT_F occupiedAreaOnScreen;
public:
	ApplicationScreen(D2D1_RECT_F occupiedAreaOnScreen);
	void Load() override;
	void Unload() override;
	void Render(Graphics* graphics) override;
	void Update() override;
};