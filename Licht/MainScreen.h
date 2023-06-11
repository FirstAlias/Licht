#pragma once
#include "Screen.h"

class MainScreen : public Screen
{
	void Load() override;
	void Unload() override;
	void Render(Graphics* graphics) override;
	void Update() override;
};

