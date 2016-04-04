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

void Cell::findNeighboors(int xlength, int ylength)
{
	int i,j;
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
		{
			//Starting point is 1 above and left of current
			neighboors[j][i].x = myLocation.x+j-1;
			neighboors[j][i].y = myLocation.y+i-1;
			if (myLocation.x+j-1 < 0)
				neighboors[j][i].x = xlength-1;
			if (myLocation.y+i-1 < 0)
				neighboors[j][i].y = ylength-1;
			if (myLocation.x+j-1 > xlength-1)
				neighboors[j][i].x = 0;
			if (myLocation.y+i-1 > ylength-1)
				neighboors[j][i].y = 0;
		}
	return;
}

void Cell::calcLiveNeighboors(CellArray& totalCells, int lengthx, int lengthy)
{
	int x,y,i,j;
	liveNeighboors = 0;
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
		{
			x = neighboors[j][i].x;
			y = neighboors[j][i].y; 
			
			//Wrap borders (0 indexed x value)
			if (x + 1 > lengthx)
				x = 0;
			else if (x < 0)
				x = lengthx-1;
			if (y + 1 > lengthy)
				y = 0;
			else if (y < 0)
				y = lengthy-1;
		
			Cell tempCell = totalCells.getCell(x,y);
			if ( tempCell.getLive() && (i != 1 || j != 1))
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
	for(int i=0; i<y+1; i++) //y-1?
		for(int j=0; j<x+1; j++) //x-1?
		{
//			*(rootLocation+lengthx*i+j) = Cell(j,i); //cache issue?
			(*this).setCell(j,i, Cell(j,i));
			Cell tempCell = (*this).getCell(j,i);
			tempCell.findNeighboors(x,y);
			//only called once per cell
			(*this).setCell(j,i, tempCell);
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

void CellArray::setCellLive(int j, int i)
{
	Cell tempCell = this->getCell(j,i);
	tempCell.setLive(true);
	this->setCell(j,i,tempCell);
	return;
}

void CellArray::iterate(void)
{
	for (int i=0; i<lengthy; i++)
		for (int j=0; j<lengthx; j++)
		{
			Cell tempCell = this->getCell(j,i);
			tempCell.calcLiveNeighboors((*this), lengthx, lengthy);
			tempCell.calcNextState();
			this->setCell(j,i, tempCell);
		}
	for (int i=0; i<lengthy; i++)
		for (int j=0; j<lengthx; j++)
		{
			Cell tempCell = this->getCell(j,i);
			tempCell.nextState();
			this->setCell(j,i, tempCell);
		}
}

