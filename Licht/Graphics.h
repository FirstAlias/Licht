#pragma once
#include <Windows.h>
#include <d2d1.h>

class Graphics
{
	ID2D1Factory* factory; // Used to create various graphics resources
	ID2D1HwndRenderTarget* renderTarget; // Where the graphics is drawn
public:
	Graphics();
	~Graphics();

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }

	bool Init(HWND windowHandle);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }
};