#pragma once

#define PI  3.141592

class Image;

struct Body {

	float x;
	float y;
	float r;
	float vecSize;
	float angle;


};


class Main
{
	Image* mBkBuff;
private:

	Body b[50];


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

