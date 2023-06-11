#pragma once
#include "Graphics.h"

// Abstract Class
class Screen
{
public:
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render(Graphics* graphics) = 0;
	virtual void Update() = 0; // needs timing (timeDelta, timeTotal)
};