#include <ctype.h>
#include "process.h"
#include "../myDir/myDir.h"
#include "../cscd340hw8.h"



//int valid = 0;  // 0 = false, 1 = true

void forkIt(char **argv, LinkedList* historyList)
{
	pid_t pid = fork();
    int status;
    
    
    
    if(pid < -1){	
	perror("error in fork()!!!!");
	exit(-99);
   }

	if(pid != 0)  // Parent is always non - zero
	{
		 waitpid(pid, &status, 0);

	}
	
	else
	{
		char *at;
		if(strcmp(argv[0],"history") == 0){
			printList(historyList,printType);
			exit(getpid());
		}

		else if((at = strchr(argv[0], '!')) != NULL)
		{
			int id;
			if(argv[0][1] == '!'){
				int lastId = getLastId(historyList);
				printf("lastid: %d\n", --lastId);
				print_execByID(historyList, lastId);
				exit(getpid());
			}
			else
			{
				printf("\n");
				id = atoi(at+1);

				printf("testing id: %d \n", id);
				if (id >= 0 && id <= HISTCOUNT) {
					print_execByID(historyList, id);
					exit(getpid());
				}
				else {
					printf("Invalid format, please type the number right after the !. ex: !12\n");
				}
				exit(getpid());
			}
			exit(getpid());
		}

		else{
			if(execvp(argv[0], argv) < 0)
			{
				perror("Error on child execution");
				exit(getpid());
			}
			exit(getpid());
		}
		exit(getpid());
	}

}// end forkit

void command(char* s, LinkedList* historyList)
{
	int preCount = 0, postCount = 0, pipeCount = 0, argc;
	char **prePipe = NULL, **postPipe = NULL, **argv = NULL;

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

	}// end while




}


