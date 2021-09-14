// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "Callback.h"
#include "WindowTypes.h"

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    typedef enum PADDLE { RIGHT_PADDLE, LEFT_PADDLE }; // boolean used to idenify each paddle

    // initialize windows
    Paddle leftPaddle;
    leftPaddle.init(hInstance, nCmdShow, WndProc, T("Left Paddle"));
    leftPaddle.updateWindowRect();

    Paddle rightPaddle;
    rightPaddle.init(hInstance, nCmdShow, WndProc, T("Right Paddle"));
    rightPaddle.updateWindowRect();

    Ball ball;
    ball.init(hInstance, nCmdShow, WndProc, T("Ball"));
    ball.updateWindowRect();

    // set the window positions
    float leftPaddleX = ball.getSize();
    float leftPaddleY = ball.getYScreenSize() / 2.0 - leftPaddle.getYSize() / 2.0;
    
    float rightPaddleX = ball.getXScreenSize() - rightPaddle.getXSize() - ball.getSize();
    float rightPaddleY = ball.getYScreenSize() / 2.0 - rightPaddle.getYSize() / 2.0;

    leftPaddle.setPosition(leftPaddleX, leftPaddleY, LEFT_PADDLE);
    rightPaddle.setPosition(rightPaddleX, rightPaddleY, RIGHT_PADDLE);

    ball.setPosition(-100.0, leftPaddleY); // start ball on the left side

    // Main message loop:
    MSG msg;
    bool running = true;

    while (running)
    {
        SetFocus(ball.getHWND());

        // user input (ball window is on top, so take that as input)
        while (PeekMessage(&msg, ball.getHWND(), 0, 0, PM_REMOVE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDBLCLK:
                BringWindowToTop(leftPaddle.getHWND());
                BringWindowToTop(rightPaddle.getHWND());
                //BringWindowToTop(ball.getHWND());
                break;
            // when key is pressed
            case WM_KEYDOWN:
                switch (msg.wParam)
                {
                case 'Q':
                    running = false;
                    break;
                // left paddle input
                case 'W':
                    leftPaddle.resetTimer();
                    leftPaddle.moveUp();
                    break;
                case 'S':
                    leftPaddle.resetTimer();
                    leftPaddle.moveDown();
                    break;
                case 'D':
                    if (ball.isAPointWon() == Ball::RIGHT_POINT) // if the right won a point, launch from the left
                    {
                        ball.launch(LEFT_PADDLE, leftPaddleX, leftPaddle.getMidPointY());
                        ball.resetTimer();
                    }
                    break;
                // right paddle input
                case VK_UP:
                    rightPaddle.resetTimer();
                    rightPaddle.moveUp();
                    break;
                case VK_DOWN:
                    rightPaddle.resetTimer();
                    rightPaddle.moveDown();
                    break;
                case VK_LEFT:
                    if (ball.isAPointWon() == Ball::LEFT_POINT) // if the left won a point, launch from the right
                    {
                        ball.launch(RIGHT_PADDLE, rightPaddleX, rightPaddle.getMidPointY());
                        ball.resetTimer();
                    }
                    break;
                }
                break;
            // when key is released
            case WM_KEYUP:
                switch (msg.wParam)
                {
                // left paddle input
                case 'W':
                    leftPaddle.stop();
                    break;
                case 'S':
                    leftPaddle.stop();
                    break;
                // right paddle input
                case VK_UP:
                    rightPaddle.stop();
                    break;
                case VK_DOWN:
                    rightPaddle.stop();
                    break;
                }
                break;
            }
        }

        // move the windows and run game logic
        bool leftCollision = ball.detectCollision(leftPaddle.getX(),
            leftPaddle.getY(),
            leftPaddle.getXSize(),
            leftPaddle.getYSize(), true);

        bool rightCollision = ball.detectCollision(rightPaddle.getX(),
            rightPaddle.getY(),
            rightPaddle.getXSize(),
            rightPaddle.getYSize(), false);

        //if (leftCollision || rightCollision)
        //{
        //    leftPaddle.incrementSensitivity();
        //    rightPaddle.incrementSensitivity();
        //}

        leftPaddle.update();
        rightPaddle.update();
        ball.update();

        // check if a point has been one
        if (ball.isAPointWon() != Ball::NO_POINTS)
        {
            if (ball.isAPointWon() != Ball::LEFT_POINT)
                ball.waitToLaunch(LEFT_PADDLE, leftPaddleX, leftPaddle.getMidPointY());
            else
                ball.waitToLaunch(RIGHT_PADDLE, rightPaddleX, rightPaddle.getMidPointY());

            leftPaddle.resetSensitivity();
            rightPaddle.resetSensitivity();
        }

        ball.updateWindow();

        // prevent cpu from throttling
        Sleep(0);
    }

    // close windows
    leftPaddle.release();
    rightPaddle.release();
    ball.release();

    return (int)msg.wParam;
}