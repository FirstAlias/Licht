#include "Sprite.h"

Sprite::Sprite(const wchar_t* path, Graphics* gfx)
{
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr; // HRESULT for checking errors

	// Create the wicFactory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);
	
	// Create a decoder
	IWICBitmapDecoder* wicDecoder = NULL;

	auto h = CreateFileW(
		path, GENERIC_READ, FILE_SHARE_READ,
		nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	wicFactory->CreateDecoderFromFileHandle(
		reinterpret_cast<ULONG_PTR>(h), nullptr,
		WICDecodeMetadataCacheOnLoad, &wicDecoder);

	// Read a frame from the image:
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// Create a converter
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Setup the converter
	hr = wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

	// Use the converter to create a D2D1Biotmap
	hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);

	if (wicFactory) wicFactory->Release();
	if (wicConverter) wicConverter->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicFrame) wicFrame->Release();
	CloseHandle(h);
}

Sprite::~Sprite()
{
	if (bmp) bmp->Release();
}

void Sprite::Draw(float opacity, float x, float y)
{
	gfx->GetRenderTarget()->DrawBitmap(bmp, D2D1::RectF(x, y, bmp->GetSize().width + x, bmp->GetSize().height + y), opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}
