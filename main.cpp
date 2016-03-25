#include <stdio.h>
#include <stdlib.h>
#include "conway.h"
#include <unistd.h>
#include <ncurses.h>

int main()
{
        int lengthx = 9;
	int lengthy = 9;
        CellArray totalcells(lengthx, lengthy);

	//R pentimo
	totalcells.setCellLive(4,5); //top row
	totalcells.setCellLive(4,3);
	totalcells.setCellLive(4,4); //mid row
	totalcells.setCellLive(3,4);
	totalcells.setCellLive(4,5); //bot row
//	totalcells.iterate();


	//DOES NOT SET CELLS TO LIVE! Why?
/*	Cell tempCell = totalcells.getCell(1,0);
	tempCell.setLive(true);
	totalcells.setCell(1,0,tempCell);
	totalcells.setCell(1,0,(totalcells.getCell(1,0)).setLive(true));
	(totalcells.getCell(1,1)).setLive(true);
	(totalcells.getCell(1,2)).setLive(true);
*/
//	totalcells.setCellLive(1,0);
//	totalcells.setCellLive(1,1);
//	totalcells.setCellLive(1,2);

	initscr();
	//getmaxyx(stdscr, y, x);
	for (int a=0; a<1000; a++)
	{
		for (int i=0; i<lengthy; i++)
			for (int j=0; j<lengthx; j++)
			{
				Cell tempCell = totalcells.getCell(j,i);
				if (tempCell.getLive())
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
	//	getch();
		sleep(1);
		totalcells.iterate();
	}
	getch();
	endwin();

        return 0;
}

