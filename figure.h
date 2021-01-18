#pragma once

struct Vector {

	float xvec;
	float yvec;
	float size;
	float angle;
};

inline Vector VectorMake(POINT a, POINT b) {

	float x_vec = a.x - b .x;
	float y_vec = a.y - b.y;
	float _size = sqrtf(x_vec*x_vec + y_vec*y_vec);
	float _angle = atanf(y_vec/x_vec);

	return { x_vec,y_vec,_size,_angle };

}


inline RECT RectCenter(int x, int y, int w, int h) {

	return{ x - w / 2, y - h / 2, x + w / 2, y + h / 2 };
}

inline void RRect(HDC h, RECT rc) {

	Rectangle(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, RECT rc) {

	Ellipse(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, int x, int y, int r) {

	Ellipse(h, x - r, y - r, x + r, y + r);
}

inline void RLine(HDC h, int x, int y, int ex, int ey) {

	MoveToEx(h, x, y, NULL);
	LineTo(h, ex, ey);
}

inline bool IntersectRectToCircle(RECT rc, int x, int y, int radius)
{
	if ((rc.left <= x && x <= rc.right) ||
		(rc.top <= y && y <= rc.bottom))
	{
		RECT newRect = rc;
		newRect.left -= radius;
		newRect.right += radius;
		newRect.top -= radius;
		newRect.bottom += radius;

		if ((newRect.left <= x && x <= newRect.right) &&
			(newRect.top <= y && y <= newRect.bottom))
		{
			return true;
		}
	}

	POINT a = { x,y };
	POINT b = { rc.left, rc.top };
	POINT c = { rc.right, rc.top };
	POINT d = { rc.right, rc.bottom };
	POINT e = { rc.left, rc.bottom };

	Vector Q = VectorMake(a, b);
	Vector W = VectorMake(a, c);
	Vector E = VectorMake(a, d);
	Vector R = VectorMake(a, e);

	
	if (radius >= abs(Q.size))return true;
	//우상단
	if (radius >= abs(W.size))return true;
	//좌하단
	if (radius >= abs(E.size))return true;
	//우하단
	if (radius >= abs(R.size))return true;

	
	return false;
}

