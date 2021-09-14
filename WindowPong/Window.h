#pragma once

#include <Windows.h>
#include <tchar.h>

#include "Callback.h"

#define T(x) (TCHAR*)_T(x)

class Window
{
public:
	Window();
	Window(HINSTANCE hInstance, int nCmdShow, WNDPROC f, TCHAR* szWindowClass);
	~Window();

	bool init(HINSTANCE hInstance, int nCmdShow, WNDPROC f, TCHAR *szWindowClass);
	bool release();

	void moveWindow(float sizeX, float sizeY);

	virtual void update();

	// getters
	HWND getHWND() { return mHwnd; } // return window object
	int getXScreenSize() { return wSizeX; }
	int getYScreenSize() { return wSizeY; }

private:
	HINSTANCE mHinst;

protected:
	HWND mHwnd;

	float x, y;

	int wSizeX; // horizontal window size
	int wSizeY; // vertical window size
};

