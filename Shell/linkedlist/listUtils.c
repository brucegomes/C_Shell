#include "listUtils.h"



Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) )
{
	Node* nn = (Node*)calloc(1, sizeof(Node));
	nn -> data = buildData(fin); 
	nn -> next = NULL;	
	nn -> prev = NULL;
	return nn;
}



Node * buildNode_Type(void * passedIn)
{
	Node * newNode = (Node*)calloc(1, sizeof(Node));
	
	newNode -> data = (history*)passedIn; //might have to declare first
	newNode -> next = NULL;
	newNode -> prev = NULL;

	
	return newNode;
}



void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
	if(theList == NULL)
	   exit(-99);
	   
	else if(theList -> size <= 1)
		printf("List is Empty or Only one Element.....Nothing to sort");
		
	else
	{
	Node *min, *start, *search;
	history *temp = NULL;
	
		for(start = theList -> head->next; start -> next != NULL; start = start -> next)
		{
		  min = start;
		  
		  for(search = start -> next; search != NULL; search = search -> next)
		  {
			  if(compare(search -> data, min -> data) < 0)
			  min = search;
		  }
	       temp = min -> data;
	       min -> data = start -> data;
	       start -> data = temp;
		}
	}	
	
}



void buildList(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in))
{
	if((total <= 0) || (myList == NULL))
		exit(-99);
	
//	Node* nn;
	rewind(fin);
	int x;
	
	for(x = 0; x < total; x++)
	{

		Node* nn = buildNode(fin, buildData);
		addLast(myList, nn);
		
	}
	
}

void print_execByID(LinkedList *historyList, int id) {

	int found = 0;
	printf("testing print and exec id: %d \n", id);
	Node *cur = historyList->head;
	while (cur->next != NULL) {
		cur = cur->next;
		if (compare(cur->data, id) == 0) {
			found = 1;
			break;
		}
	}

	char s[MAX] = "No Such Command\n";
	if (found == 1) {
		history *temp = (history *) cur->data;

		s[0] = '\0';
		printf("command found: ");
		int i;
		for (i = 0; i < temp->argc; i++) {
			//concat string together
			strcat(s, temp->argv[i]);
				strcat(s, " ");
		}

		strip(s);
		printf("%s\n", s);

		command(s, historyList);
	}
}

int getLastId(LinkedList* historyList) {

	Node* cur =  historyList->head;
	while(cur->next != NULL)
		cur = cur->next;

	history* hist = (history*)cur->data;
	return hist->id;
}