#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/files.h"
#include "include/structs.h"
#include "include/list.h"
#include "include/algorithms.h"

int main(int argc, char **argv) {
	int alg = 1;
	if (argc < 2) {
		printf("CHOOSE ALGORITHM:\n0) BRUTE FORCE 1) CLOSEST PAIR\n\n");
		return EXIT_FAILURE;
	} else {
		alg = atoi(argv[1]);
	}

	/* Use a list to keep flights data at same altitude */
	Node *head = NULL;

	readInput(&head); // Read stdin and fill list
	
	/* Iterate over data */
	Node *flight = head;
	while (flight != NULL) {
		Point *p = flight->data.points; // Flights' location
		int n = flight->data.n; // Number of flights
		Danger dg; // Structure to save closest pair

		/* Compute closest pair of points with chosen algorithm */
		dg = alg ? closestPair(p, n) : bruteForce(p, n);

		// if (alg == 0) 
		// 	dg = bruteForce(p, n);
		// else if (alg == 1)
		// 	dg = closestPair(p, n);
		// else
		// 	dg = closestD(p, n);
		
		//printf("MIN: %lf\n", dg.distance);
		showPoints(dg.p1, dg.p2); // Show closest points

		// for (int i = 0; i < n; i++) {
		// 	printf("%lf %lf\n", p[i].x, p[i].y);
		// }

		// printf("\n");
		// quickSort(p, 0, n-1, smallY);
		// for (int i = 0; i < n; i++) {
		// 	printf("%lf %lf\n", p[i].x, p[i].y);
		// }
		
		flight = flight->next; // Next flights at same altitude

		free(p); // Free airplanes positions
	}

	/* Free list */
	freeList(head);
	
	return 0;
}