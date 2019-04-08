#include "obj.h"
#include <iostream>

vector3 obj::update(vector3 point)
{
	proj.m[0] = 1; proj.m[1] = 0; proj.m[2] = 0; proj.m[3] = 0;
	proj.m[4] = 0; proj.m[5] = 1; proj.m[6] = 0; proj.m[7] = 0;
	proj.m[8] = 0; proj.m[9] = 0; proj.m[10] = 1; proj.m[11] = 0;
	proj.m[12] = 0; proj.m[13] = 0; proj.m[14] = 1; proj.m[15] = 1;
	vector4 a(point, 1);
	a = proj * view * model *  a;
	vector3 p = a.homogenized();
	p.x = p.x / p.z;
	p.y = p.y / p.z;
	p = p.screen_translation();
	return p;
}

void obj::line(int x, int y, int x1, int y1)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x1, y1);
}

void obj::line(vector3& p1, vector3& p2)
{
	MoveToEx(hdc, p1.x, p1.y, NULL);
	LineTo(hdc, p2.x, p2.y);
}







