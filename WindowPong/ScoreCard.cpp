#include "ScoreCard.h"

#include <string>

void ScoreCard::update()
{	
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mHwnd, &ps);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	std::string text = std::to_string(leftScore);

	SelectObject(hdc, hFont);
	DrawTextA(hdc, text.c_str(), text.size(), &leftRect, DT_CENTER);

	text = std::to_string(rightScore);
	
	DrawTextA(hdc, text.c_str(), text.size(), &rightRect, DT_CENTER);

	EndPaint(mHwnd, &ps);
	ReleaseDC(mHwnd, hdc);

	UpdateWindow(mHwnd);
}

void ScoreCard::setFullscreen()
{
	width = GetSystemMetrics(SM_CXFULLSCREEN);
	height = GetSystemMetrics(SM_CYFULLSCREEN);
	SetWindowPos(mHwnd, HWND_TOP, 0, 0, width, height, SWP_NOCOPYBITS);
}

void ScoreCard::reset()
{
	leftRect;
	leftRect.left = width / 2 - fontSize;
	leftRect.right = leftRect.left + fontSize;
	leftRect.top = height / 2 - fontSize;
	leftRect.bottom = leftRect.top + fontSize;

	rightRect = leftRect;
	rightRect.left += fontSize;
	rightRect.right += fontSize;

	hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Courier New");

	leftScore = 0;
	rightScore = -1;
}

void ScoreCard::countPoint(int paddleType)
{
	if (paddleType == LEFT_PADDLE)
	{
		InvalidateRect(mHwnd, NULL, true);
		leftScore++;
	}
	else if (paddleType == RIGHT_PADDLE) 
	{
		InvalidateRect(mHwnd, NULL, true);
		rightScore++;
	}
}
