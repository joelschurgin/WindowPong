#pragma once

#include "Window.h"
#include "Timer.h"

class Paddle : public Window
{
public:
	void update() override;

	void updateWindowRect();
	void setPosition(float _x, float _y, bool isLeft);

	void moveUp();
	void moveDown();
	void stop();

	void incrementSensitivity();
	void resetSensitivity();

	void resetTimer();

	// getters
	float getX() { return x; }
	float getY() { return y; }

	float getXSize() { return sizeX; }
	float getYSize() { return sizeY; }

	float getMidPointX() { return x + sizeX / 2.0; }
	float getMidPointY() { return y + sizeY / 2.0; }
private:
	int sizeX = 1;
	int sizeY = 250;

	float startSensitivity = 0.000001;
	float sensitivity = startSensitivity;

	float ySpeed = 0.0;

	bool isLeftPaddle = true;

	Timer timer;
};

