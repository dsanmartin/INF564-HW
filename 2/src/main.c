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

	readInput(&head); // Read stdin 
	
	/* Iterate over data */
	Node *flight = head;
	while (flight != NULL) {
		Point *p = flight->data.points; // Flights' location
		int n = flight->data.n; // Number of flights
		double *M = (double *) malloc(n * n * sizeof(double)); // Distance Matrix
		Danger *ds = (Danger *) malloc(n * n * sizeof(Danger)); // Danger structure
		Danger *tmp = (Danger *) malloc(n * n * sizeof(Danger)); // Danger temp structure

		printf("Altitude %d\n", flight->data.id);
		
		/* Using distance matrix */
		printf("Distance Matrix:\n");
		start = clock();
		distanceMatrix(p, M, n);
		min(p, M, n);
		end = clock();
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		/* Using sorting algorithm */
		printf("Sorting algorithm:\n");

		printf("Selection Sort\n"); 
		start = clock();
		warningFlights(ds, p, n); // Compute distances
		selectionSort(ds, n * n);
		end = clock();
		printf("Min: %lf, p1: (%lf, %lf), p2: (%lf, %lf)\n", ds[0].distance, ds[0].p1.x, ds[0].p1.y, ds[0].p2.x, ds[0].p2.y);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		printf("Bubble Sort\n");
		start = clock();
		warningFlights(ds, p, n); // Compute distances
		bubbleSort(ds, n * n);
		end = clock();
		printf("Min: %lf, p1: (%lf, %lf), p2: (%lf, %lf)\n", ds[0].distance, ds[0].p1.x, ds[0].p1.y, ds[0].p2.x, ds[0].p2.y);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

		printf("Merge Sort\n");
		start = clock();
		warningFlights(ds, p, n); // Compute distances
		mergeSort(ds, tmp, 0, n * n);
		end = clock();
		printf("Min: %lf, p1: (%lf, %lf), p2: (%lf, %lf)\n", ds[0].distance, ds[0].p1.x, ds[0].p1.y, ds[0].p2.x, ds[0].p2.y);
		printf("Time: %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
		
		flight = flight->next; // Next flights at same altitude

		// Free
		free(p);
		free(M);
		free(ds);

		printf("\n");
	}

	/* Free list */
	freeList(head);

	return 0;
}