#include "StaticWindow.h"

void StaticWindow::update()
{
	MoveWindow(mHwnd, (int)x, (int)y, hSize, vSize, false);
}

void StaticWindow::move(int _x, int _y, int sizeX, int sizeY)
{
	x = _x;
	y = _y;
	hSize = sizeX;
	vSize = sizeY;

	update();
}

