#include "Hero.h"

int main()
{
	CMap GameMap;
	CHero m_Hero;
	bool isGameWorking=true;
	GameMap.generateMap();
	GameMap.createBorders();
	GameMap.renderMap();
	char key;
	do
	{
		GameMap.updateMap();
		m_Hero.changeNeeds();
		if (m_Hero.checkNeeds())
		{
			system("cls");
			std::cout <<std::endl<< "You died!" << std::endl;
			break;
		}
		key = _getch();
		m_Hero.move(key, GameMap);
	}
	while(isGameWorking);
	return 0;
}