#include <iostream>
#include <conio.h>
#include "Hero.h"

CHero::CHero()
{
    m_nXPos = 1;
    m_nYPos = 1;
    m_nHealth = 50;
    m_nDamage = 1;
    m_nDefense = 0;
    previousChar = 4;

}
CHero::~CHero()
{
    m_Inventory.clear();
}
void CHero::changePos(short YChange, short XChange, CMap *map)
{
    if (map->getSymbolNumber(m_nXPos + XChange, m_nYPos + YChange) != Wall && 
        map->getSymbolNumber(m_nXPos + XChange, m_nYPos + YChange) != Foe)
    {
        map->setSymbolNumber(m_nXPos, m_nYPos, previousChar);
        map->makeMapChange(m_nXPos, m_nYPos);
        m_nXPos += XChange;
        m_nYPos += YChange;
        previousChar = map->getSymbolNumber(m_nXPos, m_nYPos);
        map->setSymbolNumber(m_nXPos, m_nYPos, Player);
        map->makeMapChange(m_nXPos, m_nYPos);
    }
}
void CHero::move(char key, CMap *map)
{
    switch (key)
    {
        case 'w':
        {
            changePos(-1, 0, map);
            break;
        }
        case 'd':
        {
            changePos(0, 1, map);
            break;
        }
        case 's':
        {
            changePos(1, 0, map);
            break;
        }
        case 'a':
        {
            changePos(0, -1, map);
            break;
        }
    }
}
