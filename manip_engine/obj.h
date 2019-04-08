#pragma once
#include "linal.h"
#include <Windows.h>
class obj
{
public:
	obj() {}
	obj(HDC hdc) :hdc(hdc){}
	~obj(){}
	inline void set_cam_data(float d, float a1, float a2)
	{
		cam_dist = d;
		cam_ang_x = a1;
		cam_ang_y = a2;
	}
	inline void set_hdc(HDC hdc)
	{
		this->hdc = hdc;
	}

	void line(int x, int y, int x1, int y1);
	void line(vector3& p1, vector3& p2);


	virtual vector3 update(vector3 point);
	float cam_dist;
	float cam_ang_x;
	float cam_ang_y;
	HDC hdc;

	matrix4x4 proj;
	matrix4x4 model;
	matrix4x4 view;
	
};

