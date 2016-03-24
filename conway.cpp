#include <stdlib.h>
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

void Cell::setLive(bool live)
{
	liveNow = live;
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

void Cell::calcLiveNeighboors(CellArray& totalCells, int lengthx, int lengthy)
{
	int x,y,i,j;
	for (i=-1; i<2; i++)
		for (j=-1; j<2; j++)
		{
			x = neighboors[i][j].x;
			y = neighboors[i][j].y;
			
			//Wrap borders (0 indexed x value)
			if (x + 1 > lengthx)
				x = 0;
			if (y + 1 > lengthy)
				y = 0;

			if ( totalCells(x,y).getLive() && (i != 0 && j != 0))
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

CellArray::CellArray(int x, int y)
{
	lengthx = x; lengthy = y;
	rootLocation = (Cell*) malloc(sizeof(Cell)*x*y);
	for(int i=0; i<y; i++)
		for(int j=0; j<x; j++)
		{
//			*(rootLocation+lengthx*i+j) = Cell(j,i); //cache issue?
			(*this)(j,i) = Cell(j,i);
			//only called once per cell
			(*this)(j,i).findNeighboors();
		}

}

CellArray::~CellArray(void)
{
	lengthx = 0; lengthy = 0;
	free(rootLocation);
}

Cell& CellArray::operator()(int j, int i)
{
	return *(rootLocation + i*lengthx + j);
}

void CellArray::iterate(void)
{
	for (int i=0; i<lengthx-1; i++)
		for (int j=0; j<lengthy-1; j++)
		{
			(*this)(j,i).calcLiveNeighboors((*this), lengthx, lengthy);
			(*this)(j,i).calcNextState();
			(*this)(j,i).nextState();
		}
}

