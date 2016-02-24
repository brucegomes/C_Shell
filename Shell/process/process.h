#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../linkedlist/linkedList.h"
#include "../linkedlist/genericData.h"
#include "../linkedlist/listUtils.h"
#include "../utils/fileUtils.h"

void forkIt(char ** argv, LinkedList* historyList);
void command(char* s, LinkedList* historyList);

#endif
