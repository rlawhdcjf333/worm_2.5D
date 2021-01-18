#include "pch.h"
#include "Image.h"

Image::Image()
	:mImageBuffer(NULL), mIsTrans(0)
{}

Image::~Image() {
	ReleaseBuffer();
}

void Image::ReleaseBuffer() {
	if (mImageBuffer != NULL) {
		SelectObject(mImageBuffer->hdc, mImageBuffer->oldBitm);
		DeleteObject(mImageBuffer->bitm);

		delete mImageBuffer;
		mImageBuffer = NULL;
	}
}

bool Image::CreateEmpty(int w, int h) {

	if (mImageBuffer != NULL) {

		ReleaseBuffer();
	}

	HDC hdc = GetDC(g_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadt = LoadType::Empty;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitm = (HBITMAP)CreateCompatibleBitmap(hdc, w, h);
	mImageBuffer->oldBitm = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitm);
	mImageBuffer->w = w;
	mImageBuffer->h = h;

	ReleaseDC(g_hWnd, hdc);

	if (mImageBuffer->bitm == NULL) {
		ReleaseBuffer();
		return false;
	}

	return false;
}

void Image::Render(HDC hdc, int x, int y) {

	BitBlt(
		hdc, x, y,
		mImageBuffer->w, mImageBuffer->h,
		mImageBuffer->hdc, 0, 0, SRCCOPY);
}