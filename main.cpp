#include "pch.h"
#include "main.h"
#include "Image.h"


void Main::Init() {

	SetTimer(g_hWnd, 1, 10, NULL);

	mBkBuff = new Image();
	mBkBuff->CreateEmpty(WINSIZEX, WINSIZEY);

	b[0] = { 100, WINSIZEY / 2, 15, 5, 0 };

	for (int i = 1; i < 50; i++) {

		b[i].r = 15;
		b[i].x = b[i - 1].x + b[i].r*2;
		b[i].y = b[i - 1].y;
	}

}

void Main::Release() {

	KillTimer(g_hWnd, 1);

	Random::ReleaseInstance();

	delete mBkBuff;
	mBkBuff = NULL;

}

void Main::Update() {
	
	if (Input::GetInstance()->GetKey(VK_LEFT) ) { //angle control input
		b[0].angle += 0.05;
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT)) {
		b[0].angle -= 0.05;
	}

	b[0].x += b[0].vecSize * cos(b[0].angle); 
	b[0].y += b[0].vecSize * (-sin(b[0].angle));

	if (b[0].x > WINSIZEX - b[0].r) { b[0].angle = PI - b[0].angle; } //wall- reflection
	if (b[0].x < b[0].r) { b[0].angle = PI - b[0].angle; }
	if (b[0].y < b[0].r) { b[0].angle = 2 * PI - b[0].angle; }
	if (b[0].y > WINSIZEY - b[0].r) { b[0].angle = 2 * PI - b[0].angle; }

	for (int i = 1; i < 50; i++) {

		b[i].angle = Math::GetAngle(b[i].x, b[i].y, b[i - 1].x, b[i - 1].y);
		b[i].vecSize = Math::Distance(b[i].x, b[i].y, b[i - 1].x, b[i - 1].y);

		b[i].x += cos(b[i].angle) * b[i].vecSize/6; // 6으로 나누는 이유 : 몸통사이 거리(30)/대가리 vecSize(5) == 6이라서...
		b[i].y += -sin(b[i].angle) * b[i].vecSize/6;
	}



}

void Main::Render(HDC hdc) {

	HDC backDC = mBkBuff->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); {


		HBRUSH color;
		HBRUSH white;
		HPEN newP;
		HPEN black;
		HFONT newF;
		HFONT oldF;

		color = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		white = (HBRUSH)SelectObject(backDC, color);
		RRect(backDC, RectCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY));
		SelectObject(backDC, white);
		DeleteObject(color);


		for (int i = 0; i < 50;i++) {

			REllipse(backDC, b[i].x, b[i].y, b[i].r);

		}



		


	}

	mBkBuff->Render(hdc, 0, 0);
}