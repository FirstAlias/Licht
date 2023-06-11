#pragma once
#include <wincodec.h> // WIC codec header for decoding image from file
#include "Graphics.h" // Includes windows and d2d1.h

class Sprite
{
	Graphics* gfx; // Reference to the graphics class
	ID2D1Bitmap* bmp; // Bitmap loaded file and converted to Direct2D format
public:
	// The constructor reads image files using WIC and converts it into a bitmap
	Sprite(const wchar_t* path, Graphics* gfx);
	~Sprite();

	// Draw the bitmap to the render target
	void Draw(float opacity, float x, float y, float scale);
};