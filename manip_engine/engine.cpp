#include "engine.h"

LRESULT WINAPI StaticWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	engine* engine_ptr = (engine*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (engine_ptr)
	{
		return engine_ptr->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


engine::engine(): hwnd(NULL), hdc(NULL)
{
	create_window();
}

int engine::run()
{
	if (!hwnd)
	{
		MessageBoxEx(hwnd, "ERR", "ERR", MB_OK, NULL);
		return 1;
	}

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	
	//loop
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
	
		}
	}



	return 0;
}


engine::~engine()
{
	DestroyWindow(hwnd);
}

void engine::create_window()
{
	WNDCLASSEX wc;
	hInstance = GetModuleHandle(NULL);
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)StaticWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBoxEx(NULL, "RegisterClass failed", "ERROR", MB_OK, 0);
		return;
	}

	width = SCREEN_WIDTH;
	height = SCREEN_HEIGTH;

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		CLASS_NAME,
		TITLE,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
}

LRESULT engine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static bool f = true;
	static RECT rect;
	if (f)
	{
		cube.view = cube.view.identity();
		f = false;
	}
	switch (uMsg)
	{
	case WM_CREATE:
	{
		return 0;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		GetClientRect(hwnd, &rect);
		static HPEN black_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		static HPEN red_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		static HPEN blue_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		static HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
		hdc = BeginPaint(hwnd, &ps);
		HDC hCmpDC = CreateCompatibleDC(hdc);
		HBITMAP hBmp = CreateCompatibleBitmap(hdc, rect.right - rect.left,
			rect.bottom - rect.top);
		SelectObject(hCmpDC, hBmp);
		FillRect(hCmpDC, &rect, white);
		//SelectObject(hdc, black_pen);
		inp.action();
		cube.set_hdc(hCmpDC);
		cube.set_cam_data(inp.dist, inp.angle_x, inp.angle_y);
		cube.set_data(vector3(0, 0, 0), 0, inp.rot_angles[0].y, 0);
		cube.draw(0.5, 1, 0.5);
		cube.set_data(vector3(0, 2, 0), inp.rot_angles[1].x,
		inp.rot_angles[1].y+inp.rot_angles[0].y, inp.rot_angles[1].z);
		SelectObject(hCmpDC, red_pen);
		cube.draw(0.5, 1, 0.5);
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
			hCmpDC, 0, 0, SRCCOPY);
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		EndPaint(hwnd, &ps);
		
		return 0;
	}
	case WM_KEYDOWN:
		//TODO
		inp.keys[wParam] = true;
		InvalidateRect(hwnd, NULL, TRUE);
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		return 0;
	case WM_KEYUP:
		inp.keys[wParam] = false;
		return 0;
	case WM_MOUSEWHEEL:
	{
		inp.zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		InvalidateRect(hwnd, NULL, TRUE);
		//std::cout << inp.old_mouse << "\n";
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		inp.old_mouse.x = LOWORD(lParam);
		inp.old_mouse.y = HIWORD(lParam);
		//std::cout << inp.old_mouse << "\n";
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON)
		{
			inp.mouse.x = LOWORD(lParam);
			inp.mouse.y = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
			//std::cout << inp.mouse << "\n";
		}
		return 0;
	}
	
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}