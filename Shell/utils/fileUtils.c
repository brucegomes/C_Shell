//
// Created by frejat10 on 1/23/16.
//

#include <string.h>
#include "fileUtils.h"
#include "../cscd340hw8.h"

FILE* openFile(char* fileName, char* mode)
{
    if(fileName == NULL) {
        perror("filename passed in openFile is null");
        return NULL;
    }
    FILE* fin = fopen(fileName, mode);

    return fin;
}

void setGlobalVars(FILE* fin)
{
    char temp[20];
    char* at;
    fgets(temp, 20, fin);
    if((at = strchr(temp, '=')) != NULL)
    {
        HISTCOUNT = atoi(at+1);
	   printf("HISTCOUNTSET = %d\n", HISTCOUNT);
        at = NULL;
        memset(&temp[0], 0, sizeof(temp));
        fgets(temp, 20, fin);

        if((at = strchr(temp, '=')) != NULL){
            HISTFILECOUNT = atoi(at+1);
	   printf("HISTFILECOUNTSET = %d\n", HISTFILECOUNT);
	}
        else
            perror("error on changing HISTFILECOUNT value ");
    }
    else
        perror("error on changing HISTFILE value ");

    fclose(fin);
    at = NULL;
}

void loadHistList(LinkedList* histList, FILE* fin)
{
    int id, argc; char temp[50];
    char** argv;
    int total = countRecords(fin, 1);
    rewind(fin);

    int i;
    if (total <= HISTCOUNT) {
        // load the whole thing

    for(i = 0; i < total; i++)
       {
        fgets(temp, 50, fin);
        argc = makeargs(temp, &argv);
        addLast(histList, buildNode_Type(buildType_Args(argc, argv)));
       }
    }

    else
    {
        // skip till the start point
        i = 0;
        int res = total - HISTCOUNT;
        while(i < res){char trash[50];fgets(trash, 50, fin); i++;}
        while(res < total)
            {
            fgets(temp, 50, fin);
            argc = makeargs(temp, &argv);
            addLast(histList, buildNode_Type(buildType_Args(argc, argv)));
            res++;
            }
    }

    fclose(fin);
}


int countRecords(FILE * fp, int linesPerRecord)
{
  int lines = 0;

    while(!feof(fp))
    {
       if(fgetc(fp) == '\n')
          lines++;
    }

  return lines;
}


void updateMssh_history(LinkedList* histList, FILE* fin3)
{

    int i = 0;
    Node* cur = histList->head;
    if(histList->size > HISTFILECOUNT) {
        while (i < HISTFILECOUNT){cur = cur -> next; i++;}
    }
    while(cur ->next != NULL) {
        cur = cur -> next;
        history* temp = (history*)cur ->data;

           for (i = 0; i < temp->argc; i++) {
               fprintf(fin3, "%s ", temp->argv[i]);
           }
        fprintf(fin3, "\n");
       }
    fclose(fin3);
}
