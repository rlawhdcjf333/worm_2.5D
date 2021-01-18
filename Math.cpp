#include "pch.h"
#include "Math.h"


float Math::Distance(float x, float y, float xx, float yy) {

	 float distance=sqrtf((xx - x) * (xx - x) + (yy - y) * (yy - y));
	 return distance;
}



float Math::GetAngle(float x, float y, float xx, float yy) {

	float w = xx - x;
	float h = yy - y;
	float dist = sqrtf(w * w + h * h);
	
	float angle = acosf(w/dist);

	if (y < yy) {

		angle = 2 * PI - angle;
	}

	return angle;
}