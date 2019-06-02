#ifndef LIST_H
#define LIST_H

#include "structs.h"

void init(Node** head);
void printList(Node* head);
Node* add(Node* node, Flights data);
void append(Node** node, Flights data);
void freeList(Node *head);

#endif