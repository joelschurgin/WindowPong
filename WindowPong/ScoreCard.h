#pragma once

#include "Window.h"

class ScoreCard : public Window
{
public:
	void update() override;
	void setFullscreen();

	void reset();

	static enum PaddleType 
	{
		LEFT_PADDLE,
		RIGHT_PADDLE
	};

	void countPoint(int whichPaddle);
private:
	int leftScore;
	int rightScore;

	unsigned width, height;

	const int fontSize = 100;
	RECT leftRect, rightRect;
	HFONT hFont;
};

