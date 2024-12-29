#pragma once

#include <Windows.h>

namespace WindowPong 
{
	extern bool running;
};

LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);