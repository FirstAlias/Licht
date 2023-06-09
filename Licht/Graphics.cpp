#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);
	if (res != S_OK) return false;
	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r/255, g/255, b/255));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r/255, g/255, b/255, a/255), &brush);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y), radius, radius), brush, 3.0f);
	brush->Release();
}

void Graphics::DrawBorder(float width, float r, float g, float b, float clientWidth, float clientHeight)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r / 255, g / 255, b / 255), &brush);

	for (int i = 0; i < width; i++)
	{
		// Left
		renderTarget->DrawLine(D2D1::Point2F(i, 0), D2D1::Point2F(i, clientHeight), brush);

		// Right
		renderTarget->DrawLine(D2D1::Point2F(i, 0), D2D1::Point2F(i, clientHeight), brush);

		// Top
		renderTarget->DrawLine(D2D1::Point2F(i, 0), D2D1::Point2F(i, clientHeight), brush);

		// Bottom
		renderTarget->DrawLine(D2D1::Point2F(i, 0), D2D1::Point2F(i, clientHeight), brush);
	}
	brush->Release();
}

void Graphics::DrawBorderFade1C(float width, float r, float g, float b, float r1, float g1, float b1, float clientWidth, float clientHeight, float xOffset, float yOffset, bool H = true, bool V = true)
{
	ID2D1SolidColorBrush* brush;

	// Against potentially uninitialized local pointer variable usage error message -- bad code
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush);

	// Width = 2
	// Line 1 = Border Color
	// Line 2 = (Border Color + Background Color) / 2

	// Width = 3
	// Line 1 = Border Color
	// Line 2 = (2 * Border Color + Background Color) / 3
	// Line 3 = (2 * Background Color + Border Color) / 3
	
	// Width = 4
	// Line 1 = Border Color
	// Line 2 = (3 * Border Color + Background Color) / 4
	// Line 3 = (2 * Border Color + 2 * Background Color) / 4
	// Line 4 = (3 * Background Color + Border Color) / 4

	width += xOffset;
	for (int i = xOffset; i < width; i++)
	{
		float factor1 = width - i;
		float factor2 = i;

		renderTarget->CreateSolidColorBrush(D2D1::ColorF((factor1 * (r / 255) + factor2 * (r1 / 255)) / width, (factor1 * (g / 255) + factor2 * (g1 / 255)) / width, (factor1 * (b / 255) + factor2 * (b1 / 255)) / width), &brush);
		
		// Left
		if (H)
			renderTarget->DrawLine(D2D1::Point2F(i, yOffset + (i - xOffset)), D2D1::Point2F(i, clientHeight - yOffset - (i - xOffset)), brush);

		// Right
		if (H)
			renderTarget->DrawLine(D2D1::Point2F(clientWidth - i, yOffset + (i - xOffset)), D2D1::Point2F(clientWidth - i, clientHeight - yOffset - (i - xOffset)), brush);

		// Top
		if (V)
			renderTarget->DrawLine(D2D1::Point2F(i, yOffset + (i - xOffset)), D2D1::Point2F(clientWidth - i, yOffset + (i - xOffset)), brush);

		// Bottom
		if (V)
			renderTarget->DrawLine(D2D1::Point2F(i, clientHeight - yOffset - (i - xOffset)), D2D1::Point2F(clientWidth - i, clientHeight - yOffset - (i - xOffset)), brush);
	}

	brush->Release();
}

void Graphics::DrawBorderFade2C(float width, float r, float g, float b, float r1, float g1, float b1, float r2, float g2, float b2, float clientWidth, float clientHeight, float xOffset, float yOffset, bool V, bool H)
{
	DrawBorderFade1C(width / 8, r, g, b, (r1 + r) / 2, (g1 + g) / 2, (b1 + b) / 2, clientWidth, clientHeight, xOffset, yOffset, V, H);
	DrawBorderFade1C(width / 4, (r1 + r) / 2, (g1 + g) / 2, (b1 + b) / 2, r1, g1, b1, clientWidth, clientHeight, width/8 + xOffset, yOffset, V, H);
	DrawBorderFade1C(width / 4, r1, g1, b1, (r2 + r1) / 2, (g2 + g1) / 2, (b2 + b1) / 2, clientWidth, clientHeight, width / 8 + width / 4 + xOffset, yOffset, V, H);
	DrawBorderFade1C(width / 8, (r2 + r1) / 2, (g2 + g1) / 2, (b2 + b1) / 2, r2, g2, b2, clientWidth, clientHeight, 2 * width/4 + width/8 + xOffset, yOffset, V, H);
}
