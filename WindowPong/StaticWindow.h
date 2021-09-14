#pragma once

#include "Window.h"

class StaticWindow : public Window
{
public:
	void update() override;
	void move(int _x, int _y, int sizeX, int sizeY);
private:
	int hSize = 100;
	int vSize = 100;
};

