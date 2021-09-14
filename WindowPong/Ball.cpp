#include "Ball.h"

void Ball::update()
{
	
	// update speed
	if (waitingToLaunch) // exit if the ball is waiting to launch
		return;

	float deltaTime = timer.getDeltaTime();
	x += xSpeed * deltaTime;
	y += ySpeed * deltaTime;
	
	// check bounds
	if (x < 0 || x > wSizeX - size)
	{
		// track ball to the paddle
		waitingToLaunch = true;

		// someone gets a point
		if (x < 0)
			pointWon = RIGHT_POINT;
		else
			pointWon = LEFT_POINT;
	}

	// reverse y speed
	if (y < 0 || y > wSizeY - size)
		ySpeed *= -1.0;

	// update the window position
	updateWindow();
}

void Ball::updateWindow()
{
	moveWindow(size, size);
}

int Ball::isAPointWon()
{
	return pointWon;
}

void Ball::randomizeAngle()
{
	float theta = ((float)M_PI / 2.0 * (float)rand() / (float)RAND_MAX); // random number from 0 to pi / 2;
	theta = pow(theta, 0.65); // change the random distribution (gets more curved as the power decreases)
	
	if (ySpeed < 0.0) // retain the general direction
		ySpeed = -abs(xSpeed) * sin(theta);
	else
		ySpeed = abs(xSpeed) * sin(theta);
}

void Ball::resetTimer()
{
	timer.getDeltaTime();
}

bool Ball::detectCollision(float objX, float objY, float objXSize, float objYSize, bool isLeftPaddle)
{
	bool collisionDetected = false;

	// determines the width of the collision area
	// the actual width = size * collisionWidth
	float collisionWidth = 0.2;

	// determines the height above the paddle that still counts as a collision
	// the actual height goes from [y - size * collisionHeight, y + size * collisionHeight]
	float collisionHeight = 0.9;

	// check the rectangle collisions
	bool top = objY <= y + size * collisionHeight;
	bool bottom = objY + objYSize >= y + size * (1.0 - collisionHeight);
	bool left = false;
	bool right = false;
	
	if (isLeftPaddle)
	{
		left = objX + objXSize >= x;
		right = objX + objXSize <= x + size * collisionWidth;
	}
	else
	{
		left = objX >= x + size * (1.0 - collisionWidth);
		right = objX <= x + size;
	}
		
	// if point is in the rect
	if (top && bottom && left && right)
	{
		
		// reverse the ball x speed and speed up a little
		if (!previouslyCollided)
		{
			if (isLeftPaddle && xSpeed < 0.0)
				xSpeed *= -speedGrowth;
			else if (!isLeftPaddle && xSpeed > 0.0)
				xSpeed *= -speedGrowth;

			// give it a random y speed
			randomizeAngle();

			collisionDetected = true;
		}

		previouslyCollided = true;
	}
	else
	{
		previouslyCollided = false;
	}

	return collisionDetected;
}

void Ball::waitToLaunch(bool paddle, float paddleX, float paddleY)
{
	if (!waitingToLaunch)
		return;

	if (paddle) // left paddle
		x = paddleX + size;
	else // right paddle
		x = paddleX - size;

	y = paddleY - size / 2.0; // track to the paddle
}

void Ball::launch(bool startOnLeft, float paddleX, float paddleY)
{
	waitingToLaunch = false;
	pointWon = NO_POINTS;

	// randomize x and y speeds
	xSpeed = startSpeed;
	ySpeed = startSpeed * ((float)rand() / (float)RAND_MAX - 0.5);

	if (startOnLeft)
	{
		x = paddleX + size; // start on the left
	}
	else
	{
		x = paddleX - size; // start on the right
		xSpeed *= -1.0;
	}

	// update the window position
	updateWindow();
}

void Ball::updateWindowRect()
{
	// set size
	RECT rc;
	GetWindowRect(mHwnd, &rc);

	size = abs(rc.right - rc.left) * 0.9;
}

void Ball::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;

	// keep this window on top since it is responsible for handling input
	SetWindowPos(mHwnd, HWND_TOPMOST, x, y, size, size, SWP_NOREDRAW);
}
