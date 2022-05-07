#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <string>
#include <conio.h>
#include "ConsoleColor.h"
#include "Map.h"
#include <stdio.h>
#warning "Make a linked list from all entities that can move, so that you can efficiently track map changes" 
static int SEED = 5;
HANDLE m_hConsoleHandle = 0;
static int hash[] = {208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24, 140, 71, 48, 140, 254, 245, 255, 247, 247, 40,
                     185, 248, 251, 245, 28, 124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202, 224, 245, 128, 167, 204,
                     9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 100, 108, 167, 44, 43, 77, 180, 204, 8, 81,
                     70, 223, 11, 38, 24, 254, 210, 210, 177, 32, 81, 195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13,
                     203, 9, 47, 104, 125, 117, 114, 124, 165, 203, 181, 235, 193, 206, 70, 180, 174, 0, 167, 181, 41,
                     164, 30, 116, 127, 198, 245, 146, 87, 224, 149, 206, 57, 4, 192, 210, 65, 210, 129, 240, 178, 105,
                     228, 108, 245, 148, 140, 40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62, 3, 237, 55, 89,
                     232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17, 212, 203, 149, 152, 140, 187, 234, 177, 73, 174,
                     193, 100, 192, 143, 97, 53, 145, 135, 19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 39, 145,
                     101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42, 30, 154, 120, 67, 87, 167,
                     135, 176, 183, 191, 253, 115, 184, 21, 233, 58, 129, 233, 142, 39, 128, 211, 118, 137, 139, 255,
                     114, 20, 218, 113, 154, 27, 127, 246, 250, 1, 8, 198, 250, 209, 92, 222, 173, 21, 88, 102, 219};

int noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int + 1, y_int);
    int u = noise2(x_int, y_int + 1);
    int v = noise2(x_int + 1, y_int + 1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for (i = 0; i < depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin / div;
}
const symbolColor mapSymbols[] =        
{
       /* {L'▓', White, Black},
        {L'▲', DarkGray, Black},
        {L'♠', Brown, Green},
        {L'♦', Cyan, Black},
        {L'¶', LightGreen, Black},
        {L'░', LightBlue, Blue},
        {L'☻', Red, Black},
        {L'☺', Blue, Black},*/
        {'#', White, Black},
        {'o', DarkGray, Black},
        {'T', Brown, Black},
        {'*', Cyan, Black},
        {',', LightGreen, Black},
        {'~', LightBlue, Blue},
        {'@', Red, Black},
        {'@', Blue, Black},
};

CMap::CMap()
{

}
CMap::~CMap()
{
}

void CMap::createBorders()
{
    for (short i = 0; i < SCREEN_WIDTH; i += SCREEN_WIDTH)
    {
        for (short k = 0; k < SCREEN_HEIGHT; ++k)
        {
            m_aScreenBuffer[i][k] = 0;
        }
    }
    for (short i = 0; i < SCREEN_WIDTH; ++i)
    {
        for (short k = 0; k < SCREEN_HEIGHT; k += SCREEN_HEIGHT)
        {
            m_aScreenBuffer[i][k] = 0;
        }
    }
}
void CMap::renderSystemInitialize()
{
    m_hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(m_hConsoleHandle, &cursorInfo);

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            m_aScreenBuffer[x][y] = 0;
        }
    }
}
void CMap::renderSystemClear()
{
    memset(m_aScreenBuffer, 0, sizeof(m_aScreenBuffer) / sizeof(m_aScreenBuffer[0]));
}

void CMap::setConsoleCursor(int x, int y)
{
    COORD cursorCoord;
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(m_hConsoleHandle, cursorCoord);
}
void CMap::setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    unsigned char consoleColor = symbolColor | (backgroundColor << 4);
    SetConsoleTextAttribute(m_hConsoleHandle, consoleColor);
}

void CMap::generateMap()
{
    createBorders();
    srand(time(0));
    for (short i = 1; i < SCREEN_WIDTH - 1; ++i)
    {
        for (short k = 1; k < SCREEN_HEIGHT - 1; ++k)
        {
            m_aScreenBuffer[i][k] =  (((short)(perlin2d(i, k, 0.1, 4) * 10)) % 5 ) + 1;
        }
    }
    m_aScreenBuffer[1][1] = Player;
}

short CMap::getSymbolNumber(int x, int y)
{
    return m_aScreenBuffer[x][y];
}
void CMap::setSymbolNumber(int x, int y, short symbol)
{
    m_aScreenBuffer[x][y] = symbol;
}
void CMap::makeMapChange(int x, int y)
{
    setConsoleColor(mapSymbols[m_aScreenBuffer[x][y]].symbolColor, mapSymbols[m_aScreenBuffer[x][y]].backgroundColor);
    setConsoleCursor(x, y);
    std::cout << mapSymbols[m_aScreenBuffer[x][y]].symbol;
    if(mapSymbols[m_aScreenBuffer[x][y]].symbol == Player)
    {
        setConsoleCursor(SCREEN_WIDTH + 2,SCREEN_HEIGHT + 2);
        std::cout << "X:" << x;
        setConsoleCursor(SCREEN_WIDTH + 2,SCREEN_HEIGHT + 3);
        std::cout << "Y:" << y;
    }
}

void CMap::updateMap()
{
    setConsoleCursor(0, 0);
    for (short i = 0; i < SCREEN_WIDTH; i++)
    {
        for (short k = 0; k < SCREEN_HEIGHT; k++)
        {
            makeMapChange(i, k);
        }
        std::cout << std::endl;
    }
}