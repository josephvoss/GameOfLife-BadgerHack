#include <stdio.h>
#include <stdlib.h>
#include "conway.h"
#include <unistd.h>
#include <ncurses.h>

int main()
{
        int lengthx, lengthy;
	initscr();
	getmaxyx(stdscr, lengthy, lengthx);
        CellArray totalcells(lengthx, lengthy);

	//R pentimo
/*	totalcells.setCellLive(4,5); //top row
	totalcells.setCellLive(4,3);
	totalcells.setCellLive(4,4); //mid row
	totalcells.setCellLive(3,4);
	totalcells.setCellLive(4,5); //bot row
*/
//Glider
	totalcells.setCellLive(0,0);
	totalcells.setCellLive(0,2);
	totalcells.setCellLive(1,1);
	totalcells.setCellLive(2,1);
	totalcells.setCellLive(1,2);

	for (int a=0; a<1000; a++)
	{
		for (int i=0; i<lengthy; i++)
			for (int j=0; j<lengthx; j++)
			{
				Cell tempCell = totalcells.getCell(j,i);
				if (tempCell.getLive())
				{
					mvaddch(i,j,254);
				}
				else
				{
					mvaddch(i,j,32);
				}
			}
		refresh();
		usleep(100000);
	//	getch();
		totalcells.iterate();
	}
	getch();
	endwin();

        return 0;
}

