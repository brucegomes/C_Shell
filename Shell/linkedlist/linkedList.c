#include "linkedList.h"

int HISTID = 0;

LinkedList * linkedList()
{
	LinkedList* myList = (LinkedList*)calloc(1, sizeof(LinkedList));
	myList->head = (Node*)calloc(1, sizeof(Node));
	myList->size = 0;
	
	return myList;	
}

void addLast(LinkedList * theList, Node * nn)
{
	if((theList == NULL) || (nn == NULL))
		exit(-99);

	Node * cur = theList -> head;
	while(cur -> next != NULL)
	{
		cur = cur -> next;
	}
	
	cur -> next = nn;
	nn -> prev = cur;
	++theList->size; // Global var
	HISTID = theList->size;
}


void addFirst(LinkedList * theList, Node * nn)
{
	if((theList == NULL) || (nn == NULL))
		exit(-99);
	
	nn -> prev = theList -> head;
	nn -> next = theList -> head -> next;
	
	if((theList -> head -> next) != NULL)
	theList -> head -> next -> prev = nn;
	
	theList -> head -> next = nn;
	theList -> size++;

}



void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
		if((theList == NULL) || (nn == NULL))
		exit(-99);
		
	Node * cur = theList -> head;
	while(cur->next != NULL)
	{
			cur = cur-> next;
			
		if(compare(cur->data, nn->data) == 0)
		{	
		   if(cur->next != NULL)
		   {
			Node* temp = cur;
			cur = cur->prev;
			cur-> next = cur-> next-> next;
			cur-> next -> prev = cur; 
			removeData(temp -> data);
			temp->next = NULL;
			temp->prev = NULL;
			free(temp);
		   }
		
		    else
		    {
				removeData(cur -> data);
				cur -> prev -> next = NULL;
				cur -> prev = NULL;
				free(cur);				
			}
			theList -> size--;
		}
		
	}

}


void clearList(LinkedList * theList, void (*removeData)(void *))
{
	if(theList != NULL)
	{
		Node * cur = theList -> head;
		while(cur != NULL)
		{
			theList -> head = cur -> next;
			removeData(cur -> data);
			free(cur);
			cur = theList -> head;
		}
		theList -> size = 0;
		free(theList -> head);
		theList -> head = NULL;
	}
	
}


void printList(const LinkedList * theList, void (*convertData)(void *))
{
	if((theList == NULL) || (theList -> size == 0))
		printf("Empty List !!!\n");
	
	else
	{
		Node * cur = theList -> head -> next;
		printf("----- LIST PRINTED -----\n");
		while(cur != NULL)
		{
		   convertData(cur -> data);
		   //printf(", ");
		   cur = cur -> next;
		   printf("\n");
		}
		
	}

}
