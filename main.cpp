#include <stdio.h>
#include <stdlib.h>
#include "conway.h"

int main()
{
        int lengthx = 9;
	int lengthy = 9;
        CellArray totalcells(lengthx, lengthy);

	//R pentimo
	totalcells(5,4).setLive(true); //top row
	totalcells(6,4).setLive(true);
	totalcells(5,5).setLive(true); //mid row
	totalcells(4,5).setLive(true);
	totalcells(5,6).setLive(true); //bot row

	for (int i=0; i++; i<1000)
		totalcells.iterate();

        return 0;
}

