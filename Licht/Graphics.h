#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
	// Used to create various graphics resources
	ID2D1Factory* factory;
	// Where the graphics is drawn -- ideally, set up to be the window non-border pixels
	ID2D1HwndRenderTarget* renderTarget;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawBorderFade1C(float width, float r, float g, float b, float r1, float g1, float b1, float clientWidth, float clientHeight, float xOffset, float yOffset, bool H, bool V);
	void DrawBorderFade2C(float width, float r, float g, float b, float r1, float g1, float b1, float r2, float g2, float b2, float clientWidth, float clientHeight, float xOffset, float yOffset, bool V, bool H);
	void DrawBorder(float width, float r, float g, float b, float clientWidth, float clientHeight);
};