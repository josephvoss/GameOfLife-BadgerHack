#include <stdio.h>
#include <stdlib.h>
#include "conway.h"

int main()
{
        int length = 8;
        cell *totalcells;
        totalcells = (cell*) malloc(sizeof(cell)*length*length);
//      cell totalcells[8][8];

        //initialize
        int i,j;
        for(i=0; i<8; i++)
                for(j=0; j<8; j++)
                        *(totalcells + i + j*8) = cell(i,j);

        return 0;
}

