#pragma once
#include "linal.h"
#include "obj.h"
#include <Windows.h>
#include <vector>
class cube : public obj
{
public:
	cube();
	~cube();
	void draw(float x, float y, float z);
	vector3 update(vector3 p);
	inline void set_data(vector3 tr, float x, float y, float z)
	{
		trans = tr;
		rot_x = x;
		rot_y = y;
		rot_z = z;
	}
	matrix4x4 model;
	float rot_x;
	float rot_y;
	float rot_z;
	vector3 trans;
};

