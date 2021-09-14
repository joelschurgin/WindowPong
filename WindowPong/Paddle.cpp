#include "Paddle.h"

void Paddle::update()
{
	y += ySpeed * timer.getDeltaTime();;
	
	y = (y < 0.0) ? 0.0 : y;
	y = (y > wSizeY - sizeY) ? wSizeY - sizeY : y;

	moveWindow(sizeX, sizeY);
}

void Paddle::updateWindowRect()
{
	// set size
	RECT rc;
	GetWindowRect(mHwnd, &rc);

	sizeX = abs(rc.right - rc.left) * 0.9;
	sizeY = abs(rc.bottom - rc.top) * 0.9;
}

void Paddle::setPosition(float _x, float _y, bool isLeft)
{
	x = _x;
	y = _y;
	SetWindowPos(mHwnd, HWND_NOTOPMOST, x, y, sizeX, sizeY, SWP_NOREDRAW);

	isLeftPaddle = isLeft;
}

void Paddle::moveUp()
{
	ySpeed = -sensitivity;
	update();
}

void Paddle::moveDown()
{
	ySpeed = sensitivity;
	update();
}

void Paddle::stop()
{
	ySpeed = 0.0;
	update();
}

void Paddle::incrementSensitivity()
{
	sensitivity += 0.01 * startSensitivity;
}

void Paddle::resetSensitivity()
{
	sensitivity = startSensitivity;
}

void Paddle::resetTimer()
{
	timer.getDeltaTime();
}
