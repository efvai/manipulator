#include "cube.h"


cube::cube(): trans(0), rot_x(0), rot_y(0), rot_z(0)
{
}


cube::~cube()
{
}


void cube::draw(float x, float y, float z)
{
	std::vector<vector3> *points = new std::vector<vector3>;
	vector3 temp(0);
	temp = { -x,-y,-z }; points->push_back(temp);
	temp = { -x, y, -z }; points->push_back(temp);
	temp = { x, y, -z }; points->push_back(temp);
	temp = { x, -y, -z }; points->push_back(temp);
	temp = { -x, -y, -z }; points->push_back(temp);
	temp = { -x, -y, z }; points->push_back(temp);
	temp = { -x, y, z }; points->push_back(temp);
	temp = { x, y, z }; points->push_back(temp);
	temp = { x, -y, z }; points->push_back(temp);
	temp = { -x, -y, z }; points->push_back(temp);
	temp = { -x, -y, -z }; points->push_back(temp);
	temp = { -x, -y, z }; points->push_back(temp);
	temp = { -x, -y, -z }; points->push_back(temp); //??
	temp = { -x, y, -z }; points->push_back(temp);
	temp = { -x, y, z }; points->push_back(temp);
	temp = { x, y, z }; points->push_back(temp); //??
	temp = { x, y, -z }; points->push_back(temp);
	temp = { x, y, z }; points->push_back(temp);
	temp = { x, y, -z }; points->push_back(temp); //??
	temp = { x, -y, -z }; points->push_back(temp);
	temp = { x, -y, z }; points->push_back(temp);
	//std::cout << view;
	for (auto it = points->begin(); it != points->end() - 1; it++)
	{
		vector3 point_1 = *it;
		vector3 point_2 = *(it + 1);
		point_1 = update(point_1);
		point_2 = update(point_2);
		obj::line(point_1, point_2);
	}
	delete points;
}

vector3 cube::update(vector3 point)
{
	view = view.identity() * view.trans(vector3(0, 0, cam_dist)) 
		* view.rot_y(cam_ang_y) * view.rot_x(cam_ang_x);

	/*matrix4x4 temp_z = temp_z.identity() * temp_z.trans(vector3(0, -0.5, 0))
		* temp_z.rot_x() * temp_z.rot_y(0) * temp_z.rot_z(rot_z)
		* temp_z.inverse(temp_z.rot_y(0)) * temp_z.inverse(temp_z.rot_x(0))
		* temp_z.inverse(temp_z.trans(vector3(0, 0.5 ,0)));*/
	obj::model = model.identity() * model.rot_y(rot_y) * model.trans(trans)
		* model.trans(vector3(0, -0.5, 0)) 
		* model.rot_x(rot_x) * model.rot_z(rot_z) 
		* model.trans(vector3(0, 0.5, 0));
	vector4 a(point, 1);
	vector4 temp = view * model * a;
	//std::cout << point << "\n";
	std::cout << temp << "\n";
	vector3 p = obj::update(point);
	return p;
}

