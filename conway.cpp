#include "conway.h"

Cell::Cell(int x, int y)
{
	myLocation.x = x; myLocation.y = y;
	liveNeighboors=0; liveNow=false;
}

int Cell::getX(void)
{
	return myLocation.x;
}

int Cell::getY(void)
{
	return myLocation.y;
}

bool Cell::getLive(void)
{
	return liveNow;
}

void Cell::setLocation(int x, int y)
{
	myLocation.x = x;
	myLocation.y = y;
	return;
}

void Cell::findNeighboors(void)
{
	int i,j;
	for (i=-1; i<2; i++)
		for (j=-1; j<2; j++)
		{
			neighboors[i][j].x = myLocation.x+i;
			neighboors[i][j].y = myLocation.y+j;
		}
	return;
}

void Cell::calcLiveNeighboors(Cell* totalCells, int length)
{
	int x,y,i,j;
	for (i=-1; i<2; i++)
		for (j=-1; j<2; j++)
		{
			x = neighboors[i][j].x;
			y = neighboors[i][j].y;
			
			//Wrap borders (0 indexed x value)
			if (x + 1 > length)
				x = 0;
			if (y + 1 > length)
				y = 0;

			if ( (*(totalCells + i + j*length)).getLive() && (i != 0 && j != 0))
				liveNeighboors += 1;
		}
	return;
}

void Cell::calcNextState(void)
{
	//Born if 3, stays alive if 2 or 3
	if (!liveNow && liveNeighboors == 3)
		liveNext = true;
	else if (liveNow && (liveNeighboors == 2 || liveNeighboors == 2))
		liveNext = true;
	else
		liveNext = false;
	
	return;
}

void Cell::nextState(void)
{
	liveNow = liveNext;
	liveNext = false;
	return;
}
