//
// Created by frejat10 on 1/23/16.
//

#include <stdio.h>
#include "../linkedlist/linkedList.h"
#include <stdlib.h>

#ifndef LAB8_FILEUTILS_H
#define LAB8_FILEUTILS_H




FILE* openFile(char* fileName, char* mode);
void setGlobalVars(FILE* fin);   // in case .msshrc exists it loads the global var s from it
void loadHistList(LinkedList* histList, FILE* fin);  // loads hist file into linked list
int countRecords(FILE * fin, int linesPerRecord);
//void updateMssh_history(int listSize, int argc, char** argv, FILE* fin3); // writes linked list into the history file
void updateMssh_history(LinkedList* histList, FILE* fin3);

#endif //LAB8_FILEUTILS_H