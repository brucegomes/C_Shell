#include "pipes.h"

int containsPipe(char *s)
{
	char** argv = NULL;
	int i,pipes = 0, argc;
	char s2[50];
	strcpy(s2, s);
	strip(s2);
	argc = makeargs(s2, &argv);
	
	for(i = 0; i < argc; i++)
	{
		if(strchr(argv[i], '|') != NULL)
		pipes++; 
	}
//	printf("%d pipes found within command\n", pipes);
	
	clean(argc, argv);
	
	return pipes;
}


char ** parsePrePipe(char *s, int * preCount)
{
	char** prePipe;
	*preCount = 0;
	char *saveptr;
    char *buffer;	 
    
	char** argv = NULL;
	int i, argc;
	char s2[50];
	strcpy(s2, s);
	strip(s2);
	argc = makeargs(s2, &argv);
	
	
	for(i = 0; i < argc; i++)
	{
		if(strchr(argv[i], '|') != NULL)
		{
		if((strlen(argv[i]) > 1) && (argv[i][0] != '|' ))
		*preCount = *preCount +1;
		
		break;	
		}
		else
		{
		*preCount = *preCount +1;
	    }
	}
	
//	printf("preCount: %d\n", *preCount);
	if(*preCount > 0){
	
	prePipe = (char**)calloc((size_t)*preCount+1, sizeof(char*)); // +1 is for null row at last
	for(i = 0; i < *preCount; i++)
	{
	 strip(argv[i]);	
	 buffer = strtok_r(argv[i], "|", &saveptr);
	 prePipe[i] = (char*)calloc((int)strlen(buffer)+1, sizeof(char));
	 strcpy(prePipe[i], argv[i]);
	 buffer = NULL;
	 saveptr = NULL;
	}
	
	/*
	for(i = 0; i < *(preCount); i++)
	{
	printf("prePipe[i] is: %s\n", prePipe[i]);
	} */
	
	clean(argc, argv);
    }
	
	return prePipe;
}



char ** parsePostPipe(char *s, int * postCount)
{
	char** postPipe;
	*postCount = 0;

	char s2[50];
	strcpy(s2, s);
	strip(s2);
	char** argv = NULL;
	int i, argc, start = -1;
	argc = makeargs(s2, &argv);
	
	
	for(i = 0; i < argc; i++)
	{
		if(strchr(argv[i], '|') != NULL)
		{
			start = i;						
			
		if((strlen(argv[i]) > 1) && (argv[i][strlen(argv[i])-1] != '|' )){
		    *postCount = *postCount +1;
		}
		
		i++;
		
		while(i < argc){*postCount = *postCount +1; i++;}
		
		//printf("postCount: %d\n",*postCount);
		}
	}
	
	postPipe = (char**)calloc(*postCount+1, sizeof(char*)); // +1 is for null row at last
	
	
	if(*postCount > 0)
	{
		i = 0;
				
	  char* at = strchr(argv[start], '|');
	 	  
	  if(at != NULL && strlen(at) > 1)
		{
		postPipe[0] = (char*)calloc((int)strlen(at + 1)+1, sizeof(char));
		strcpy(postPipe[0], (at + 1));
		i = 1;

		}
			start++;

	while(i < *postCount)
	{
		
		strip(argv[start]);
		postPipe[i] = (char*)calloc((int)strlen(argv[start])+1, sizeof(char));
		strcpy(postPipe[i] ,argv[start]);
		start++;
		i++;
	}
	
}	

/*	for(i = 0; i < *(postCount); i++)
	{
	printf("postPipe[%d] is: %s\n", i, postPipe[i]);
	}*/ 
	printf("\n");
	
	clean(argc, argv);
	
	return postPipe;
}




void pipeIt(char ** prePipe, char ** postPipe, LinkedList* historyList)
{
	
	pid_t pid, pid2;
	int fd[2], res, status = 55;
/*	res = pipe(fd);
     
	if(res < 0)
	{
		printf("Pipe Failure\n");
		exit(-1);
	}// end if*/

	pid = fork();

	if(pid != 0)
	{
	   
       waitpid (pid, &status, 0);
   	 /*  close (fd[1]);
       dup2(fd[0], 0);
       close (fd[0]);
	   if (check = execvp(postPipe[0], postPipe) < 0) {
            perror("Error on Parent execution");
            exit(1);	}*/
	
	  
	}// end if AKA parent
	
	else
	{
	
	res = pipe(fd);
    if(res < 0)
	{
		printf("Pipe Failure\n");
		exit(-1);
	}// end if
	
	pid2 = fork();
	
		if(pid2 != 0) // new parent
	   {
		  
		waitpid (pid2, &status, 0);
		
		close (fd[1]);
		dup2(fd[0], 0);
		close (fd[0]);
	   if (execvp(postPipe[0], postPipe) < 0) {
            perror("Error on Parent execution");
            exit(getpid());
		}
		
		exit(getpid());
	  }
	   
	   else{  //new Child
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);

		//TODO
		// maybe call exec to print hist_count file or linked list

			if(strcmp(prePipe[0],"history") == 0){
				/*if(execlp("less", "less",".mssh_history", NULL) < 0)
				{
					perror("Error on child execution");
					exit(getpid());
				}*/
				printList(historyList,printType);
				exit(getpid());
			}

			else{
					if(execvp(prePipe[0], prePipe) < 0)
					{
					perror("Error on child execution");
					exit(getpid());
					}
				}

		exit(getpid());
	   }
		
		
		exit(getpid());
	}// end else AKA child
	

	
}
