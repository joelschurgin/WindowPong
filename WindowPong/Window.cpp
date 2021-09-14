#include "Window.h"

Window::Window() : mHwnd(NULL), mHinst(NULL), x(0), y(0), wSizeX(0), wSizeY(0)
{
	
}

Window::Window(HINSTANCE hInstance, int nCmdShow, WNDPROC f, TCHAR* szWindowClass) : mHwnd(NULL), mHinst(NULL), x(0), y(0)
{
	init(hInstance, nCmdShow, f, szWindowClass);
}

Window::~Window()
{

}

bool Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC f, TCHAR *szWindowClass)
{
	// window class object
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;//LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;// LoadIcon(wcex.hInstance, IDI_APPLICATION);

	// register the window object
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Window Pong"),
			NULL);

		return false;
	}

	mHinst = hInstance;

	// create the window
	mHwnd = CreateWindow(
		szWindowClass,
		szWindowClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// check that the window was created
	if (!mHwnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Window Pong"),
			NULL);

		return false;
	}

	// show the window
	ShowWindow(mHwnd, nCmdShow);
	UpdateWindow(mHwnd);

	// get window size;
	wSizeX = GetSystemMetrics(SM_CXFULLSCREEN);
	wSizeY = GetSystemMetrics(SM_CYFULLSCREEN);

	update();

	return true;
}

bool Window::release()
{
	if (mHwnd)
	{
		if (!DestroyWindow(mHwnd))
			return false;
	}

	return true;
}

void Window::moveWindow(float sizeX, float sizeY)
{
	MoveWindow(mHwnd, (int)x, (int)y, (int)sizeX, (int)sizeY, false);
}

void Window::update()
{
	moveWindow(500, 500);
}
