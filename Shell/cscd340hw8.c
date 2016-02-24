#include "cscd340hw8.h"


int HISTCOUNT;
int HISTFILECOUNT;

int main()
{
	char originalPWD[MAX];
	getcwd(originalPWD, sizeof(originalPWD));
	printf("cur dir: %s \n", originalPWD);
	char s[MAX];



	LinkedList *historyList = linkedList();
	FILE *fin = openFile(".msshrc", "r");
	if (fin == NULL) {
		HISTCOUNT = 100; HISTFILECOUNT = 1000;
		printf(".msshrc not present\n");
	}
	else
	setGlobalVars(fin);

	FILE* fin2 = openFile(".mssh_history", "r");
	if(fin2 == NULL){
		printf(".mssh_history not present\n");
	}
	else
		loadHistList(historyList, fin2);

	printf("\ncommand?: ");
	fgets(s, MAX, stdin);
	strip(s);

	command(s, historyList);

/*  printf("\ncommand?: ");
  fgets(s, MAX, stdin);
  strip(s);

  while(strcmp(s, "exit") != 0)
  {
	 	  char s2[50];
	 	  strcpy(s2, s);
	  	  strip(s2);
	   	  argc = makeargs(s2, &argv);
	   	  addLast(historyList, buildNode_Type(buildType_Args(argc, argv)));
	      memset(&s2[0], 0, sizeof(s2));

	pipeCount = containsPipe(s);
	if(pipeCount > 0)
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe, historyList);
		clean(preCount, prePipe);
		clean(postCount, postPipe);
	}// end if pipeCount	  

	else
	{
		if(strcmp(argv[0],"cd") != 0) {
			if (argc != -1)
				forkIt(argv, historyList);
		}
		else
			myDir(argv);
	}
	  //	clean(argc, argv);
	  //	argv = NULL;

     //printList(historyList,printType);

	memset(&s[0], 0, sizeof(s));
	printf("\ncommand?: ");
	fgets(s, MAX, stdin);
      	strip(s);

  }// end while    */

	printf("exit on PWD: %s\n", originalPWD);
	chdir(originalPWD);
	FILE* fin3 = openFile(".mssh_history", "w"); //truncate
	if(fin3 != NULL)
		updateMssh_history(historyList, fin3);

	clearList(historyList, cleanType);
	free(historyList);


	return 0;

}// end main

