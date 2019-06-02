#include <stdio.h>
#include <stdlib.h>
#include "include/structs.h"

void append(Node** head, Flights data) { 

	Node *new = (Node *) malloc(sizeof(Node)); 
	Node *last = *head; 

	new->data = data; 
	new->next = NULL; 

	if (*head == NULL)
		*head = new; 
	else {
		while (last->next != NULL) 
			last = last->next; 
		last->next = new; 
	}

} 

void printList(Node *node) { 
	while (node != NULL) { 
		printf("%d\n", node->data.id); 
		for (int i = 0; i < node->data.n; i++) {
			printf("%lf %lf\n", node->data.points[i].x, node->data.points[i].y);
		}
		node = node->next; 
	} 
} 

void freeList(Node *head) {
	Node *tmpPtr = head;
	Node *followPtr;
	while (tmpPtr != NULL) {
		followPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		free(followPtr);
	}
}