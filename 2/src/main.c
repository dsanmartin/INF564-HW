#include <stdio.h>
#include <stdlib.h>
#include "include/files.h"
#include "include/structs.h"
#include "include/list.h"
#include "include/algorithms.h"

int main(int argc, char **argv) {
	int alg = 1;
	if (argc < 2) {
		printf("USE: ./tarea2 ALG < input.\nALG: (0) BRUTE FORCE (1) CLOSEST PAIR\n");
		return EXIT_FAILURE;
	} else {
		alg = atoi(argv[1]);
	}

	/* Use a list to keep flights data */
	Node *head = NULL; // This was implemented using list for debugging process...

	readInput(&head); // Read stdin and fill list
	
	/* Iterate over data */
	Node *flight = head;
	while (flight != NULL) {
		Point *p = flight->data.points; // Flights' location
		int n = flight->data.n; // Number of flights
		Danger dg; // Structure to save closest pair and min distance

		/* Compute closest pair of points with chosen algorithm */
		dg = alg ? closestPair(p, n) : bruteForce(p, n);
		
		//printf("MIN: %lf\n", dg.distance);
		showPoints(dg.p1, dg.p2); // Show closest points
		
		flight = flight->next; // Next flights

		free(p); // Free airplanes positions
	}

	/* Free list */
	freeList(head);
	
	return 0;
}