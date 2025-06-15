#include <ncurses.h>
#include "Hero.h"


int main(void)
{
    
    CMap GameMap;
    CHero Hero;
    bool isGameWorking = true;
    setlocale(LC_ALL, "");
    initscr();			/* Start curses mode 		*/
    raw();				/* Line buffering disabled	*/
    start_color();
    GameMap.renderSystemInitialize();
    GameMap.generateMap();
    GameMap.updateMap();
    char key;
    do
    {
        key = getch();
        if(key == 'q')
        {
            break;
        }
        Hero.move(key, &GameMap);
        GameMap.updateMap();
    } while (isGameWorking);
	endwin();			/* End curses mode		  */
    return 0;
}
