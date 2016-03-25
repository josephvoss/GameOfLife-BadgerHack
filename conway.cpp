#include <stdlib.h>
#include <stdio.h>
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
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
		{
			//Starting point is 1 above and left of current
			neighboors[j][i].x = myLocation.x+j-1;
			neighboors[j][i].y = myLocation.y+i-1;
	/*		if (myLocation.x+i < 0 || myLocation.y+j < 0) //or greater than
			{
				neighboors[i][j].x = myLocation.x+i;
				neighboors[i][j].y = myLocation.y+j;
			}
			else
			{
				neighboors[i][j].x = -1;
				neighboors[i][j].y = -1;
			}*/
		}
	return;
}

void Cell::calcLiveNeighboors(CellArray& totalCells, int lengthx, int lengthy)
{
	int x,y,i,j;
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
		{
			x = neighboors[j][i].x;
			y = neighboors[j][i].y; 
			
			//Wrap borders (0 indexed x value)
		/*	if (x + 1 > lengthx)
				x = 0;
			else if (x < 0)
				x = lengthx-1;
			if (y + 1 > lengthy)
				y = 0;
			else if (y < 0)
				y = lengthy-1;
		*/

			if ( (totalCells.getCell(x,y)).getLive() && (i != 1 || j != 1))
				liveNeighboors += 1;
		}
	return;
}

void Cell::calcNextState(void)
{
	//Born if 3, stays alive if 2 or 3
	if (!liveNow && liveNeighboors == 3)
		liveNext = true;
	else if (liveNow && (liveNeighboors == 2 || liveNeighboors == 3))
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
	for(int i=0; i<y; i++) //y-1?
		for(int j=0; j<x; j++) //x-1?
		{
//			*(rootLocation+lengthx*i+j) = Cell(j,i); //cache issue?
			(*this).setCell(j,i, Cell(j,i));
			//only called once per cell
			(*this).getCell(j,i).findNeighboors();
		}

}

CellArray::~CellArray(void)
{
	delete[] rootLocation;
}

Cell CellArray::getCell(int j, int i)
{
	if (i > -1 && i < lengthy && j > -1 && j < lengthx)
		return *(rootLocation + i*lengthx + j);
	else
	{
		Cell invalidCell = Cell(-1, -1);
		invalidCell.setLive(false);
		return invalidCell;
	}
}

void CellArray::setCell(int j, int i, Cell newCell)
{
	if (i > -1 && i < lengthy && j > -1 && j < lengthx)
		*(rootLocation + i*lengthx + j) = newCell;
	return;
}	

void CellArray::iterate(void)
{
	for (int i=0; i<lengthx; i++)
		for (int j=0; j<lengthy; j++)
		{
			(*this).getCell(j,i).calcLiveNeighboors((*this), lengthx, lengthy);
			(*this).getCell(j,i).calcNextState();
			(*this).getCell(j,i).nextState();
		}
}

