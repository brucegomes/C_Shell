#include "makeArgs.h"

void clean(int argc, char **argv)
{
	if(argc > 0){
		
 int i;
 for(i = 0; i < argc; i++)
 {
	free(argv[i]);
	argv[i] = NULL;	
 }

free(argv);
argv = NULL;
}

}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
   int argc = -1;
   char *saveptr;
   char *buffer;	 
   char** temp = NULL; 
   int totalArgv = 0, totalTemp = 0;
   
   buffer = strtok_r(s, " \n\t", &saveptr);
  
   if(buffer != NULL){	     //in casefirst time is null'
	
	int i = 0, j;
	argc = 0;	   
		   
   do{

   argc ++;
   totalArgv = argc;
  
   if(argc == 1)
   {
   *argv = (char**)calloc(argc+1, sizeof(char*)); //no null row yet
    
    totalArgv = argc+1;
      
   (*argv)[i] = (char*)calloc((int)strlen(buffer)+1, sizeof(char));
   //  (*argv)[i+1] = (char*)calloc((int)strlen(buffer)+1, sizeof(char));
   strcpy((*argv)[i], buffer);
   }
   
   
   
           //copying argv to temp array for realloc
   temp = (char**)calloc(argc, sizeof(char*));
   totalTemp = argc;
   
   for(j = 0; j < argc; j++)
   {
	temp[j] = (char*)calloc(strlen((*argv)[j]) + 1, sizeof(char));   
	strcpy(temp[j], (*argv)[j]);   
	strip(temp[j]);
	strip((*argv)[j]);
   }

  
   clean(totalArgv, *argv);  
   
   // realloc
   *argv = (char**)calloc(argc+2, sizeof(char*)); //no null row yet
   
   totalArgv = argc+2;
   
   for(j = 0; j < argc; j++)
   {
	(*argv)[j] = (char*)calloc((int)strlen(temp[j])+1, sizeof(char));
    strcpy((*argv)[j], temp[j]);
    strip(temp[j]);
	strip((*argv)[j]);
   }

   buffer = NULL;
   buffer = strtok_r(NULL, " \n\t", &saveptr);
  
 if(buffer != NULL){ 
	 
   (*argv)[argc] = (char*)calloc((int)strlen(buffer)+1, sizeof(char)); //copy new element
   
  // (*argv)[argc+1] = (char*)calloc((int)strlen(buffer)+1, sizeof(char)); //NULL ROW
  
   strcpy((*argv)[argc], buffer);
   
   strip((*argv)[argc]);
  
  }
  
   clean(totalTemp, temp);
   
   i++;
   
   }while( buffer != NULL);
   
}
 
 
 temp = NULL;
 saveptr = NULL;
 buffer = NULL;	 
 argv = NULL; 
 
   return argc;

}// end makeArgs
