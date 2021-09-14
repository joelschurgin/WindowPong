#pragma once

#include <random>
#include <math.h>

#include "Window.h"
#include "Timer.h"

#define M_PI 3.14159265358979323846

class Ball : public Window
{
public:
	// runtime methods
	void update() override;
	void updateWindow();

	int isAPointWon();

	bool detectCollision(float objX, float objY, float objXSize, float objYSize, bool isLeftPaddle);

	void waitToLaunch(bool paddle, float paddleX, float paddleY); // called when ball hits a wall (and a point is scored)
	void launch(bool startOnLeft, float paddleX, float paddleY);

	void randomizeAngle();

	void resetTimer();

	// methods used for setting up
	void updateWindowRect();
	void setPosition(float _x, float _y);

	// getters
	int getSize() { return size; }
private:
	// boolean to check if the ball is currently colliding with a paddle
	bool previouslyCollided = false;

	// this marks the point when a ball is being held by a paddle after a point is scored
	bool waitingToLaunch = false;

	// store if a point is won
	int pointWon = LEFT_POINT; // start with the left paddle

	// initial ball speed
	float startSpeed = 0.0000005;

	float xSpeed = startSpeed;
	float ySpeed = startSpeed;

	// multiplier for each paddle hit, so the ball speeds up over time
	float speedGrowth = 1.1;

	// use the minimum window width allowed by Windows
	int size = 1;

	// used instead of monitoring the framerate
	SYSTEMTIME currT = { 0 };
	SYSTEMTIME prevT = { 0 };

	// timer used to keep motion consistent
	Timer timer;
public:
	enum
	{
		NO_POINTS, LEFT_POINT, RIGHT_POINT
	};
};

