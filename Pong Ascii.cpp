#include <iostream>
#include <chrono>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;


// TODO:
// - add AI to the other player
// - add ball-player collision

int main()
{
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

   
    int nPlayer1Y = nScreenHeight / 2; 
    int nPlayer1_pos = nScreenWidth * nPlayer1Y + 3;
    int nPlayer2Y = nScreenHeight / 2;
    int nPlayer2_pos = nScreenWidth * nPlayer2Y + nScreenWidth - 4;
    int nBallY = nScreenHeight/2;
    int nBallX = nScreenWidth;
    int nBallXCorrection = nBallX / 2;
    int nBallStart_pos = (nScreenHeight / 2) * (nScreenWidth) - nScreenWidth/2;
    
    
    int nBallSpeedX = 1;
    int nBallSpeedY = 1;
    int nTemp;

    while (1)
    {
        
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float>elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();
        int nBall_pos = (nBallY * nBallX)-nBallXCorrection;
        //player goes up
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            nPlayer1_pos -= nScreenWidth;
            //collision detection
            if (nPlayer1_pos <= (nScreenWidth * 2) + 3)
            {
                nPlayer1_pos = (nScreenWidth * 2) + 3;
            }
        }
        //player goes down
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            nPlayer1_pos += nScreenWidth;
            //collision detection
            if (nPlayer1_pos >= (nScreenWidth * (nScreenHeight-2))+3)
            {
                nPlayer1_pos = (nScreenWidth * (nScreenHeight - 3)) + 3;
            }
        }
      
        nBallY += nBallSpeedY;
        nBallXCorrection -= nBallSpeedX;
        
        if ((nBallY>=nScreenHeight-2) || (nBallY <=3))
        {
            nBallSpeedY *= -1;
        }

        if ((nBallXCorrection >= nScreenWidth - 1) || (nBallXCorrection <= 3))
        {
            nBallY = nScreenHeight / 2;
            nBallXCorrection = nBallX / 2;
            nBallSpeedX *= -1;
        }

        if (nBall_pos - 1 == nPlayer1_pos)
        {
            nBallSpeedX *= -1;
        }
        
            
        Sleep(50);
        for (int x = 0; x < nScreenWidth; x++)
        {
            for (int y = 0; y < nScreenHeight; y++)
            {
                
                nTemp = y * nScreenWidth + x;
                if (y < 2 || y>nScreenHeight - 3)//horizontal borders
                {
                    screen[nTemp] = '-';
                }
                else if ((nTemp)-(y * nScreenWidth) < 2 || (nTemp)-(y * nScreenWidth) > nScreenWidth - 3) //vertical borders
                {
                    screen[nTemp] = '|';
                }
                else if (nTemp == nPlayer1_pos) //rendering player1
                {
                    screen[nTemp] = 0x2588;
                }
                else if (nTemp == nPlayer2_pos) //rendering player2
                {
                    screen[nTemp] = 0x2588;
                }
                else if (nTemp == nBall_pos) //drawing ball
                {
                    screen[nBall_pos] = 'O';
                }
                else
                { 
                    screen[nTemp] = ' ';
                }
            }
        }

        //displaying stats
        swprintf_s(screen, 40, L"FPS=%3.2f ", 1.0f / fElapsedTime);
        screen[nScreenHeight * nScreenWidth - 1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }


    return 0;
}