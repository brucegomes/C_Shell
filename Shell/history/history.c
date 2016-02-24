#include "history.h"


void * buildType_Args(int argc, char **argv)
{
	if(argc == 0)
	exit(-99);
	
	history* new = (history*)calloc(1, sizeof(history));
	new->argc = argc;
	new->argv = argv; 
	new->id = HISTID+1;

	return new;
}


void printType(void * passedIn)
{
	history* History = (history*)passedIn; 
	int i;
    printf("%-d ", History->id);
	for(i = 0; i < History->argc; i++)
	{
	   printf("%-s ", History->argv[i]);
	}
	
}


void * buildType(FILE * fin)
{
 char* null = NULL;	
	// ????????
	
	return NULL;
}


int compare(const void * p1,const int p2)
{
	return ((history *) p1)->id - p2;
}


void cleanType(void * passedIn)
{
	history * Hist = (history*)passedIn;
	
  	if(Hist)
	{
		int i = 0;
		while (i < Hist->argc) {
			free(Hist->argv[i]);
 			Hist->argv[i] = NULL;
			i++;
		}
		free(Hist->argv);
		free(Hist);
 // Hist = NULL;
	}
}
