#include "Map.h"

CMap::CMap()
{
	m_nEnemyCount = 7;
	m_nCrystalTilesCount = 1;
	m_nWaterTilesCount = 7;
	m_nRockTilesCount = 4;
	m_nTreeTilesCount = 10;
}
CMap::~CMap()
{

}
void CMap::drawTile(int i, int k, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	m_aRendMap[i][k].symbol = symbol;
	m_aRendMap[i][k].symbolColor = symbolColor;
	m_aRendMap[i][k].backgroundColor = backgroundColor;
}
void CMap::generateEnemy()
{
	Enemy temp;
	temp.health = 1 + rand() % 3;
	temp.damage = 1;
	temp.gold = rand() % 20;
	temp.id = enemiesBase.size() - 1;
	++m_nEnemyCount;
	enemiesBase.push_back(temp);
}
void CMap::createBorders()
{
	for (short i = 0; i < SCREEN_WIDTH; i += SCREEN_WIDTH)
	{
		for (short k = 0; k<SCREEN_HEIGHT; ++k)
		{
			m_anUnrendMap[i][k] = 0;
		}
	}
	for (short i = 0; i < SCREEN_WIDTH; ++i)
	{
		for (short k = 0; k<SCREEN_HEIGHT; k += SCREEN_HEIGHT)
		{
			m_anUnrendMap[i][k] = 0;
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
			m_aBackBuffer[x][y].symbol = 0;
			m_aBackBuffer[x][y].symbolColor = DarkGray;
			m_aBackBuffer[x][y].backgroundColor = Black;
			m_aScreenBuffer[x][y] = m_aBackBuffer[x][y];
		}
	}
}
void CMap::renderSystemClear()
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			m_aBackBuffer[x][y].symbol = 0;
			m_aBackBuffer[x][y].backgroundColor = Black;
		}
	}
}
void CMap::renderSystemDrawChar(int x, int y, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	m_aBackBuffer[x][y].symbol = symbol;
	m_aBackBuffer[x][y].symbolColor = symbolColor;
	m_aBackBuffer[x][y].backgroundColor = backgroundColor;
}
void CMap::renderSystemDrawText(int x, int y, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	int tx = x;
	char symbol = *text;
	while (symbol != 0)
	{
		renderSystemDrawChar(tx, y, symbol, symbolColor, backgroundColor);
		tx++;
		symbol = *(++text);
	}
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
void CMap::renderSystemFlush()
{
	for (int x = 0; x<SCREEN_WIDTH; x++)
	{
		for (int y = 0; y<SCREEN_HEIGHT; y++)
		{
			if (m_aBackBuffer[x][y] != m_aScreenBuffer[x][y])
			{
				m_aScreenBuffer[x][y] = m_aBackBuffer[x][y];

				setConsoleCursor(x, y);
				setConsoleColor(m_aScreenBuffer[x][y].symbolColor, m_aScreenBuffer[x][y].backgroundColor);
				printf("%c", m_aScreenBuffer[x][y].symbol);

			}
		}
	}
	if (m_aScreenBuffer)
	{
		setConsoleCursor(0, 0);
	}
}
void CMap::generateWaterTiles(short xcoord,short ycoord)
{
	if (m_nWaterTilesCount>0)
	{
		for (short r = xcoord - (2 + rand() % 2); r < xcoord + (2 + rand() % 2); r++)
		{
			for (short j = ycoord - (2 + rand() % 2); j < ycoord + (2 + rand() % 2); j++)
			{
				if (m_anUnrendMap[r][j] != Wall && m_anUnrendMap[r][j] != Player)
				{
					m_anUnrendMap[r][j] = Water;
				}
			}
		}
		m_nWaterTilesCount--;
	}
	else
	{
		m_anUnrendMap[xcoord][ycoord] = 1 + rand() % 4;
	}
}
void CMap::generateRockTiles(short xcoord, short ycoord)
{
	if (m_nRockTilesCount>0)
	{
		for (short r = xcoord - (2 + rand() % 2); r < xcoord + (2 + rand() % 2); r++)
		{
			for (short j = ycoord - (2 + rand() % 2); j < ycoord + (2 + rand() % 2); j++)
			{
				if (m_anUnrendMap[r][j] != Wall && m_anUnrendMap[r][j] != Player)
				{
					m_anUnrendMap[r][j] = Rock;
				}
			}
		}
		m_nRockTilesCount--;
	}
	else
	{
		m_anUnrendMap[xcoord][ycoord] = 1 + rand() % 4;
	}
}
void CMap::generateMap()
{
	createBorders();
	srand(time(0));
	for (short i = 1; i < SCREEN_WIDTH - 1; ++i)
	{
		for (short k = 1; k < SCREEN_HEIGHT - 1; ++k)
		{
			m_anUnrendMap[i][k] = 1 + rand() % 6; //generating unrendered map
			if (m_anUnrendMap[i][k] == Crystal)
			{
				m_nCrystalTilesCount--;
				if (m_nCrystalTilesCount<0)
				{
					m_anUnrendMap[i][k] += 1;
				}
			}
			else if (m_anUnrendMap[i][k] == Water && i>(rand() % 24) && k>(rand() % 24))
			{
				generateWaterTiles(i, k);
			}
			else if (m_anUnrendMap[i][k] == Rock && i>(rand() % 24) && k>(rand() % 24))
			{
				generateRockTiles(i, k);
			}
			else if (m_anUnrendMap[i][k] == Foe)
			{
				generateEnemy();
				if (m_nEnemyCount<0)
				{
					m_anUnrendMap[i][k] = 1 + rand() % 4;
				}
			}
		}
		m_nCrystalTilesCount = rand() % 2;
		m_nEnemyCount = rand() % 3;
	}
	m_anUnrendMap[1][1] = Player;
}
void CMap::renderMap()
{
	renderSystemInitialize();
	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		for (int k = 0; k < SCREEN_HEIGHT; ++k)
		{
			switch (m_anUnrendMap[i][k])
			{
				case Wall:
				{
					drawTile(i, k, '#', White, Black);
					break;
				}
				case Tree:
				{
					drawTile(i, k, 'T', Brown, Black);
					break;
				}
				case Rock:
				{
					drawTile(i, k, 'o', DarkGray, Black);
					break;
				}
				case Crystal:
				{
					drawTile(i, k, '☼', Cyan, Black);
					break;
				}
				case Grass:
				{
					drawTile(i, k, ',', LightGreen, Black);
					break;
				}
				case Foe:
				{
					drawTile(i, k, 'E', Red, Black);
					break;
				}
				case Player:
				{
					drawTile(i, k, '@', Blue, Black);
					break;
				}
				case Water:
				{
					drawTile(i, k, 'W', LightBlue, Blue);
					break;
				}
			}
		}
	}
}
ConsoleColor CMap::getTileColor(int x, int y)
{
	return m_aRendMap[x][y].backgroundColor;
}
ConsoleColor CMap::getSymbolColor(int x, int y)
{
	return m_aRendMap[x][y].symbolColor;
}
void CMap::updateMap()
{
	for (short i = 0; i<SCREEN_WIDTH; i++)
	{
		for (short k = 0; k<SCREEN_HEIGHT; k++)
		{
			if (m_anUnrendMap[i][k]==Player)
			{
				drawTile(i, k, '@', Blue, Green);
			}
			renderSystemDrawChar(i, k, m_aRendMap[i][k].symbol, m_aRendMap[i][k].symbolColor, m_aRendMap[i][k].backgroundColor);
			renderSystemFlush();
		}
		std::cout << std::endl;
	}
}