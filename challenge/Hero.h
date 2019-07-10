#pragma once
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
	std::vector <Item> m_Inventory;
	Needs m_HeroNeeds;
	Resources m_HeroResources;
	Armour m_Armour;
	Item m_InHand1;
	Item m_InHand2;
	ConsoleSymbolData previousChar;
public:
	CHero();
	~CHero();
	void move(char key, CMap& map);
	void changePos(short YChange, short Xchange, CMap& map);
	void changeNeeds();
	void fightEnemy(bool isYCoordinate, bool isPositive, CMap& map);
	void showResources();
	void showNeeds();
	void showEquipment();
	void showActions();
	void chooseAction(char key);
	void gatherResources();
	bool checkNeeds();
};