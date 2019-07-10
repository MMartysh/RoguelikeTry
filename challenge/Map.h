#pragma once
#include "ConsoleColor.h"

const short SCREEN_WIDTH=80;
const short SCREEN_HEIGHT=25;

class CMap
{
private:
	std::vector <Enemy> enemiesBase;
	HANDLE m_hConsoleHandle = 0;
	ConsoleSymbolData m_aBackBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
	ConsoleSymbolData m_aScreenBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
	ConsoleSymbolData m_aRendMap[SCREEN_WIDTH][SCREEN_HEIGHT];
	short m_nEnemyCount;
	short m_nCrystalTilesCount;
	short m_nWaterTilesCount;
	short m_nRockTilesCount;
	short m_nTreeTilesCount ;
	short m_anUnrendMap[SCREEN_WIDTH][SCREEN_HEIGHT];
public:
	CMap();
	~CMap();
	friend class CHero;
	void drawTile(int i, int k, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void createBorders();
	void generateWaterTiles(short xcoord, short ycoord);
	void generateRockTiles(short xcoord, short ycoord);
	void generateMap();
	void generateEnemy();
	void renderMap();
	void renderSystemDrawChar(int x, int y, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void renderSystemDrawText(int x, int y, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void setConsoleCursor(int x, int y);
	void setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void renderSystemFlush();
	void renderSystemClear();
	void renderSystemInitialize();
	void updateMap();
	ConsoleColor getTileColor(int x, int y);
	ConsoleColor getSymbolColor(int x, int y);
};
