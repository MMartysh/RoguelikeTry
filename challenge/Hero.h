#ifndef HERO_H
#define HERO_H
#include <vector>
#include "ConsoleColor.h"
#include "Map.h"

class CHero
{
private:
	int m_nHealth;
	int m_nDamage;
	int m_nXPos;
	int m_nYPos;
	int m_nDefense;
	double m_dblMaxWeight;
	std::vector<Item> m_Inventory;
	Needs m_HeroNeeds;
	Resources m_HeroResources;
	Armour m_Armour;
	Item m_InHand1;
	Item m_InHand2;
	short previousChar;

public:
	CHero();
	~CHero();
	void move(char key, CMap *map);
	void changePos(short YChange, short Xchange, CMap *map);
};

#endif