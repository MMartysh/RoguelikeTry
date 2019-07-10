#include "Hero.h"

CHero::CHero()
{
	m_nXPos = 1;
	m_nYPos = 1;
	m_nHealth = 50;
	m_nDamage = 1;
	m_nDefense = 0;
}
CHero::~CHero()
{
	m_Inventory.clear();
}
void CHero::changePos(short YChange,short XChange, CMap& map)
{
	if (map.m_anUnrendMap[m_nXPos + XChange][m_nYPos + YChange]!= Wall && map.m_anUnrendMap[m_nXPos+XChange][m_nYPos+YChange] != Foe)
	{
		map.m_aRendMap[m_nXPos][m_nYPos] = previousChar;
		m_nXPos += XChange;
		m_nYPos += YChange;
		previousChar = map.m_aRendMap[m_nXPos][m_nYPos];
		map.m_aRendMap[m_nXPos][m_nYPos].symbol = '@';
	}

}
void CHero::fightEnemy(bool isYCoordinate, bool isPositive, CMap& map)
{
	short change = (isPositive) ? 1 : -1;
		for (unsigned short i = 0; i<map.enemiesBase.size(); i++)
		{
			if (map.enemiesBase[i].id == i)
			{
				m_nHealth -= (map.enemiesBase[i].damage) / (m_nDefense / 2);
				map.enemiesBase[i].health -= m_nDamage;
			}
			if (map.enemiesBase[i].health <= 0)
			{
				m_HeroResources.gold += map.enemiesBase[i].gold;
				map.m_aRendMap[m_nXPos][m_nYPos - 1].symbol = ' ';
			}
		}
}
void CHero::showResources()
{
	system("cls");
	std::cout << "Wood:" << m_HeroResources.wood << std::endl;
	std::cout << "Rock:" << m_HeroResources.rock << std::endl;
	std::cout << "Seeds:" << m_HeroResources.seed << std::endl;
	std::cout << "Crystal:" << m_HeroResources.crystal << std::endl;
	std::cout << "Water:" << m_HeroResources.water << std::endl;
	std::cout << "Gold:" << m_HeroResources.gold << std::endl;
	_getch();
}
void CHero::showNeeds()
{
	system("cls");
	std::cout << "Hunger:" << m_HeroNeeds.hunger << std::endl;
	std::cout << "Thirst:" << m_HeroNeeds.thirst << std::endl;
	std::cout << "Tiredness:" << m_HeroNeeds.tiredness << std::endl;
	_getch();
}
void CHero::showActions()
{
	system("cls");
	std::cout << "Choose action: " << std::endl;
	std::cout << "1.Gather items." << std::endl;
	std::cout << "2.Eat." << std::endl;
	std::cout << "3.Drink." << std::endl;
	std::cout << "4.Change equipment." << std::endl;
	std::cout << "5.Sleep" << std::endl;
}
void CHero::gatherResources()
{
	switch (previousChar.symbol)
	{
		case 'T':
		{
			_getch();
			previousChar.symbol = ' ';
			m_HeroResources.wood += 1 + (rand() % 10);
			break;
		}
		case 'W':
		{
			_getch();
			if (m_HeroResources.water < 100)
			{
				m_HeroResources.water += 1 + (rand() % 5);
			}
			break;
		}
		case 'c':
		{
			_getch();
			previousChar.symbol = ' ';
			m_HeroResources.crystal += 1;
			break;
		}
		case 'o':
		{
			_getch();
			previousChar.symbol = ' ';
			m_HeroResources.rock += 1 + (rand() % 15);
			break;
		}
		case ',':
		{
			_getch();
			previousChar.symbol = ' ';
			m_HeroResources.seed += 1 + (rand() % 4);
			break;
		}
	}
}
void CHero::chooseAction(char key)
{
	switch (key)
	{
		case '1':
		{
			gatherResources();
			break;
		}
		case '2':
		{
			m_HeroResources.food -= 2;
			m_HeroNeeds.hunger += 10;
			break;
		}
		case '3':
		{
			m_HeroResources.water -= 2;
			m_HeroNeeds.thirst += 10;
			break;
		}
		case '5':
		{
			m_HeroNeeds.tiredness += 90;
			break;
		}
	}
	_getch();
}
void CHero::showEquipment()
{
	system("cls");
	std::cout << "Head:" << m_Armour.head.name << m_Armour.head.defense << std::endl;
	std::cout << "Torso:" << m_Armour.torso.name << m_Armour.torso.defense << std::endl;
	//std::cout<<"Arms:"<<m_Armour.arms.name<<m_Armour.arms.defense<<std::endl;
	std::cout << "Legs:" << m_Armour.legs.name << m_Armour.legs.defense << std::endl;
	std::cout << "Foot:" << m_Armour.foot.name << m_Armour.foot.defense << std::endl;
	//std::cout<<"Left hand:"<<left_hand.name<<left_hand.damage<<left_hand.defense<<std::endl;
	//std::cout<<"Right hand:"<<right_hand.name<<right_hand.damage<<right_hand.defense<<std::endl;
	std::cout << "Defense: " << m_nDefense << std::endl;
	std::cout << "Damage: " << m_nDamage << std::endl;
	_getch();
}
void CHero::move(char key,CMap& map)
{
	switch(key)
	{
		case 'w':
		{		
			if (map.m_anUnrendMap[m_nXPos][m_nYPos - 1] == Foe)
			{
				fightEnemy(true, false, map);
			}
			changePos(-1,0,map);
			break;
		}
		case 'd':
		{		
			if (map.m_anUnrendMap[m_nXPos][m_nYPos - 1] == Foe)
			{
				fightEnemy(false, true, map);
			}
			changePos(0,1,map);
			break;
		}
		case 's':
		{		
			if (map.m_anUnrendMap[m_nXPos][m_nYPos - 1] == Foe)
			{
				fightEnemy(true, true, map);
			}
			changePos(1,0,map);
			break;
		}
		case 'a':
		{
			if (map.m_anUnrendMap[m_nXPos][m_nYPos - 1] == Foe)
			{
				fightEnemy(false, false, map);
			}
			changePos(0,-1,map);
			break;
		}
		case 'g':
		{
			showActions();
			key=_getch();
			chooseAction(key);
			map.renderSystemClear();
			break;
		}
		case 'i':
		{
			showResources();
			map.renderSystemClear();
			break;
		}
		case 'o':
		{
			showEquipment();
			map.renderSystemClear();
			break;
		}
		case 'b':
		{
			if(previousChar.symbol==' ' && m_HeroResources.wood>5)
			{
				previousChar.symbol='#';
				previousChar.symbolColor=Brown;
				m_HeroResources.wood-=5;
			}
			break;
		}
		case 'n':
		{
			showNeeds();
			map.renderSystemClear();
			break;
		}
	}
}
void CHero::changeNeeds()
{
	--m_HeroNeeds.hunger;
	--m_HeroNeeds.tiredness;
	--m_HeroNeeds.thirst;
}
bool CHero::checkNeeds()
{
	return (m_HeroNeeds.hunger<0 ||	m_HeroNeeds.tiredness<0 ||	m_HeroNeeds.thirst<0);
}
