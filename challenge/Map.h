#ifndef MAP_H
#define MAP_H

#include <vector>
#include <Windows.h>
#include "ConsoleColor.h"

const short SCREEN_WIDTH=100;
const short SCREEN_HEIGHT=50;
struct symbolColor
{
    char symbol;
    ConsoleColor symbolColor;
    ConsoleColor backgroundColor;
};

class CMap
{
private:
    short m_aScreenBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
public:
    CMap();
    ~CMap();
    //friend class CHero;
    void createBorders();
    void generateMap();
    void renderMap();
    void setConsoleCursor(int x, int y);
    void renderSystemFlush();
    void renderSystemClear();
    void renderSystemInitialize();
    void updateMap();
    void makeMapChange(int x, int y);
    void setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor);
    ConsoleColor getTileColor(int x, int y);
    ConsoleColor getSymbolColor(int x, int y);
    short getSymbolNumber(int x, int y);
    void setSymbolNumber(int x, int y, short symbol);
};
#endif