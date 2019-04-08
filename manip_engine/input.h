#pragma once
#include "linal.h"
#include <iostream>

typedef struct mouse_coords
{
	mouse_coords():x(0), y(0) {}
	float x;
	float y;
} mouse_coords;



inline std::ostream& operator<<(std::ostream& out, const mouse_coords& m)
{
	out << m.x << ", " << m.y << " ";
	return out;
}

class input
{
public:
	input();
	~input() {}
	void action();
	void set_prev_mouse();
	bool keys[256];
	float angle_x;
	float angle_y;
	float dist;
	float zDelta;
	mouse_coords mouse;
	mouse_coords old_mouse;
	vector3 rot_angles[3] = { vector3(0), vector3(0), vector3(0) };
private:
	void mouse_action();
};

