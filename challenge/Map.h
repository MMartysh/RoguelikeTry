#ifndef MAP_H
#define MAP_H
#include <ncurses.h>
#include "ConsoleColor.h"

const short SCREEN_WIDTH=100;
const short SCREEN_HEIGHT=50;
struct symbolColor
{
    wchar_t symbol;
    int symbolColor;
    int backgroundColor;
};

class CMap
{
private:
    short m_aScreenBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
    WINDOW *local_win;
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
    int getTileColor(int x, int y);
    int getSymbolColor(int x, int y);
    short getSymbolNumber(int x, int y);
    void setSymbolNumber(int x, int y, short symbol);
};
#endif