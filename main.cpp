#include <stdio.h>
#include <stdlib.h>
#include "conway.h"

#include <ncurses.h>

int main()
{
        int lengthx = 3;
	int lengthy = 3;
        CellArray totalcells(lengthx, lengthy);

/*	//R pentimo
	totalcells(4,5).setLive(true); //top row
	totalcells(4,3).setLive(true);
	totalcells(4,4).setLive(true); //mid row
	totalcells(3,4).setLive(true);
	totalcells(4,5).setLive(true); //bot row
//	totalcells.iterate();
*/

	//DOES NOT SET CELLS TO LIVE! Why?
	(totalcells.getCell(1,0)).setLive(true);
	(totalcells.getCell(1,1)).setLive(true);
	(totalcells.getCell(1,2)).setLive(true);

	initscr();
	//getmaxyx(stdscr, y, x);
	for (int a=0; a<10; a++)
	{
		for (int i=0; i<lengthy; i++)
			for (int j=0; j<lengthx; j++)
			{
				if ((totalcells.getCell(j,i)).getLive())
				{
					mvaddch(i,j,254);
//					printw("L");
				}
				else
				{
					mvaddch(i,j,32);
//					printw("D");
				}
			}
	//	printw("is this thing on?\n");
		refresh();
		getch();
		totalcells.iterate();
	}
	getch();
	endwin();

        return 0;
}

