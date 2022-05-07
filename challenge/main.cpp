#include <iostream>
#include <conio.h>
#include "Hero.h"
int main()
{
    CMap GameMap;
    CHero Hero;
    bool isGameWorking = true;
    GameMap.renderSystemInitialize();
    GameMap.generateMap();
    GameMap.updateMap();
    setlocale(LC_ALL, "");
    char key;
    do
    {
        key = _getch();
        Hero.move(key, &GameMap);
    } while (isGameWorking);
    return 0;
}