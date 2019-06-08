#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/files.h"
#include "include/structs.h"
#include "include/list.h"
#include "include/algorithms.h"

int main(int argc, char *argv[]) {
	/* Use a list to keep flights data at same altitude */
	Node *head = NULL;

	/* To compute time for each approach */
	clock_t start, end;

	readInput(&head); // Read stdin and fill list
	
	/* Iterate over data */
	Node *flight = head;
	while (flight != NULL) {
		Point *p = flight->data.points; // Flights' location
		int n = flight->data.n; // Number of flights
		Danger dg;
		//int n_d = (n * n - n) / 2; // Number of distances to compute

		printf("Altitude %d\n", flight->data.id);
		
		start = clock();
		dg = bruteForceD(p, n);
		end = clock();
		printf("MIN: %lf\n", dg.distance);
		showPoints(dg.p1, dg.p2);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		start = clock();
		dg = closestD(p, n);
		//double min_c = closest(p, n);
		end = clock();
		//printf("MIN: %lf\n", min_c);
		printf("MIN: %lf\n", dg.distance);
		showPoints(dg.p1, dg.p2);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		start = clock();
		dg = prop(p, n);
		//double min_c = closest(p, n);
		end = clock();
		//printf("MIN: %lf\n", min_c);
		printf("MIN: %lf\n", dg.distance);
		showPoints(dg.p1, dg.p2);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
		
		flight = flight->next; // Next flights at same altitude

		// Free
		free(p);

		printf("\n");
	}

	/* Free list */
	freeList(head);
	
	return 0;
}