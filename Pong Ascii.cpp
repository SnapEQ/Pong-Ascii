#include <iostream>
#include <chrono>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;

int main()
{
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    int nPlayer1_pos = nScreenWidth * (nScreenHeight / 2) + 3;
    int nPlayer2_pos = nScreenWidth * (nScreenHeight / 2) + nScreenWidth - 4;
   
    
    int nTemp;

    while (1)
    {
        
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float>elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();
  
      
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            nPlayer1_pos -= nScreenWidth;
        }
        Sleep(10);
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            nPlayer1_pos += nScreenWidth;
        }
            

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
                else if (nTemp == nPlayer1_pos)
                {
                    screen[nTemp] = 0x2588;
                } 
                else if(nPlayer1_pos >= )
                {

                }
                else
                { 
                    screen[nTemp] = ' ';
                }
            }
        }
        swprintf_s(screen, 40, L"FPS=%3.2f ", 1.0f / fElapsedTime);
        screen[nScreenHeight * nScreenWidth - 1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }


    return 0;
}