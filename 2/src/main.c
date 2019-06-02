#include <stdio.h>
#include <stdlib.h>
#include "include/files.h"
#include "include/structs.h"
#include "include/list.h"
#include "include/algorithms.h"

int main(int argc, char *argv[]) {
	int *n_flights = 0;
	Node *head = NULL;

	readInput(&head, n_flights);

	//printf("N Flights: %d", n_flights);

	Node *flight = head;
	while (flight != NULL) {
		Point *p = flight->data.points;
		int n = flight->data.n;
		//distances(p, n->data.n);
		double *M = (double *) malloc(n * n * sizeof(double));
		distanceMatrix(p, M, n);
		min(p, M, n);
		
		flight = flight->next;
	}
		
	

	//printList(head);
	freeList(head);

	return 0;
}