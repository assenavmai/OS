#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "holesFunctions.h"

int main(int argc, char const *argv[])
{

	if(argc < 2)
	{
		printf("You need to enter a file name.\n");
		exit(1);
	}

	printf("-------------------------------------FIRST FIT---------------------------------\n");
	firstFit(argv[1]);

	printf("-------------------------------------BEST FIT-----------------------------------\n");
	bestFit(argv[1]);

	printf("-------------------------------------WORST FIT-----------------------------------\n");
	worstFit(argv[1]);

	printf("-------------------------------------NEXT FIT------------------------------------\n");
	nextFit(argv[1]);

	return 0;
}
