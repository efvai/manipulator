#pragma once
#include "const_header.h"
#include "obj.h"
#include "cube.h"
#include "input.h"
#include <Windows.h>
#include <iostream>


class engine
{
public:
	engine();
	~engine();

	int run();

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void create_window();

	HDC hdc;
	HWND hwnd;
	HINSTANCE hInstance;

	LONG width; //windows width
	LONG height; // windows heigth

	input inp;
	cube cube;
};

