#include <stdio.h>
#include <stdlib.h>
#include "conway.h"
#include <unistd.h>
#include <ncurses.h>

void Rpentimo(CellArray& cellarray, int lengthx, int lengthy)
{
	int centerx = (lengthx-1)/2;
	int centery = (lengthy-1)/2;
	cellarray.setCellLive(centerx,centery-1); //top row
	cellarray.setCellLive(centerx+1,centery-1);
	cellarray.setCellLive(centerx,centery); //mid row
	cellarray.setCellLive(centerx-1,centery);
	cellarray.setCellLive(centerx,centery+1); //bot row
}

void Glider(CellArray& cellarray, int lengthx, int lengthy)
{
	int centerx = (lengthx-1)/2;
	int centery = (lengthy-1)/2;
	cellarray.setCellLive(centerx-1,centery-1);
	cellarray.setCellLive(centerx-1,centery+1);
	cellarray.setCellLive(centerx,centery);
	cellarray.setCellLive(centerx+1,centery);
	cellarray.setCellLive(centerx,centery+1);
}

int main()
{
        int lengthx, lengthy;
	initscr();
	getmaxyx(stdscr, lengthy, lengthx);
	if (lengthy % 2 != 1)
		lengthy -= 1;
	if (lengthx % 2 != 1)
		lengthy -= 1;
        CellArray totalcells(lengthx, lengthy);

	Rpentimo(totalcells, lengthx, lengthy);

	for (int a=0; a<100000; a++)
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
		//getch();
		totalcells.iterate();
	}
	getch();
	endwin();

        return 0;
}

