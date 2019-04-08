#include "input.h"
#include "const_header.h"
#include "obj.h"
#include <memory>
#include <Windows.h>
#include <iostream>
#include <math.h>

input::input() 
{
	memset(this, 0, sizeof(input)); 
	dist = 5;
}

void input::action()
{
	if (keys[VK_LEFT])
	{
		rot_angles[0].y += PI / 36;
		return;
	}
	if (keys[VK_RIGHT])
	{
		rot_angles[0].y -= PI / 36;
		return;
	}
	if (keys['Q']) {
		rot_angles[1].x += PI / 36;
		return;
	}
	if (keys['W']) {
		rot_angles[1].x -= PI / 36;
		return;
	}
	if (keys['A']) {
		rot_angles[1].y += PI / 36;
		return;
	}
	if (keys['S']) {
		rot_angles[1].y -= PI / 36;
		return;
	}
	if (keys['Z']) {
		rot_angles[1].z += PI / 36;
		return;
	}
	if (keys['X']) {
		rot_angles[1].z -= PI / 36;
		return;
	}
	if (zDelta > 0)
	{
		dist += 1;
		zDelta = 0;
		return;
	}
	else if (zDelta < 0)
	{
		dist -= 1;
		zDelta = 0;
		return;
	}
	mouse_action();
}

void input::mouse_action()
{
	//old_mouse.x = old_mouse.x / (1.0 / 2) / (SCREEN_WIDTH - 2) - 1;
	//old_mouse.y = old_mouse.y / (-1.0 / 2) / (SCREEN_HEIGTH - 2) + 1;
	//mouse.x = mouse.x / (1.0 / 2) / (SCREEN_WIDTH - 2) - 1;
	//mouse.y = mouse.y / (-1.0 / 2) / (SCREEN_HEIGTH - 2) + 1;
	//std::cout << mouse << " ---- " << old_mouse << "\n";
	if ((old_mouse.x = (old_mouse.x / ((SCREEN_WIDTH - 1) / 2)) - 1) == -1)
		old_mouse.x = 0;
	if ((old_mouse.y = (old_mouse.y / ((SCREEN_HEIGTH - 1) / 2)) - 1) == -1)
		old_mouse.y = 0;
	if ((mouse.x = (mouse.x / ((SCREEN_WIDTH - 1) / 2)) - 1) == -1)
		mouse.x = 0;
	if ((mouse.y = (mouse.y / ((SCREEN_HEIGTH - 1) / 2)) - 1) == -1)
		mouse.y = 0;
	//std::cout << mouse << " ---- " << old_mouse << "\n";
	//angle = acos(old_mouse.x * mouse.x + old_mouse.y * mouse.y);
	angle_y = old_mouse.x * mouse.x * 2;
	angle_x = old_mouse.y * mouse.y * 2;
	//std::cout << angle_y << ", " << angle_x << "\n";
	old_mouse = mouse;
}

void input::set_prev_mouse()
{
	old_mouse = mouse;
}


