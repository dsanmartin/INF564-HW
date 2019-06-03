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
		int no = (n * n - n) / 2; // Number of flights (opt)
		int min_pos = 0;
		double *M = (double *) malloc(n * n * sizeof(double)); // Distance Matrix
		Danger *ds = (Danger *) malloc(n * n * sizeof(Danger)); // Danger structure
		// Danger *tmp = (Danger *) malloc(n * n * sizeof(Danger)); // Danger temp structure
		Danger *dso = (Danger *) malloc(no * sizeof(Danger)); // Danger structure Opt
		// Danger *tmpo = (Danger *) malloc(no * sizeof(Danger)); // Danger structure Opt

		printf("Altitude %d\n", flight->data.id);
		
		/* Using distance matrix */
		printf("Distance Matrix:\n");
		start = clock();
		distanceMatrix(p, M, n);
		min(p, M, n);
		end = clock();
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		/* Using sorting algorithm */
		printf("\nSearch algorithm:\n");

		printf("\nLinear search\n"); 
		start = clock();
		warningFlights(ds, p, n); // Compute distances
		//min_pos = searchMin(ds, n * n);
		// int l = 0, r = n*n;
		// int mid = l + (r - l ) / 2;
		min_pos = DACMin(ds, 0, n * n - 1);
		printf("min pos: %d\n", min_pos);
		end = clock();
		printf("Min: %lf\n", ds[min_pos].distance);
		showWarningFlights(ds[min_pos].p1, ds[min_pos].p2);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		printf("\nLinear OPT\n"); 
		start = clock();
		warningFlightsOPT(dso, p, n); // Compute distances
		//min_pos = searchMin(dso, no);
		// l = 0, r = no;
		// mid = l + (r - l ) / 2;
		min_pos = DACMin(dso, 0, no - 1);
		printf("min pos: %d\n", min_pos);
		end = clock();
		printf("Min: %lf\n", dso[min_pos].distance);
		showWarningFlights(dso[min_pos].p1, dso[min_pos].p2);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		flight = flight->next; // Next flights at same altitude

		// Free
		free(p);
		free(M);
		free(ds);
		free(dso);

		printf("\n");
	}

	/* Free list */
	freeList(head);

	return 0;
}