#include <stdio.h>
#include <stdlib.h>
#include "include/files.h"
#include "include/list.h"

/* Read input from stdin. Fill a list where each element has the flights at equal altitude */
void readInput(Node **head) {
	int id = 0, n = 0;
	printf("Reading input...\n");
	while (scanf("%d\n", &n) != EOF) { // Read n 
		/* Create flights structure and fill it */
		Flights f;
		f.id = id;
		f.n = n;
		f.points = (Point *) malloc(n * sizeof(Point));
		for (int i = 0; i < n; i++) { // Fill planes positions
			Point p;
			scanf("%lf %lf\n", &p.x, &p.y);
			f.points[i] = p;
		}
		append(head, f); // Append to list of flights
		id++; // Identifier of flights at same altitude (just informative)
	}
}

void showWarningFlights(Point p1, Point p2) {
	if (p1.x < p2.x) {
		printf("%lf %lf\n%lf %lf\n", p1.x, p1.y, p2.x, p2.y);
	} else if (p1.x > p2.x) {
		printf("%lf %lf\n%lf %lf\n", p2.x, p2.y, p1.x, p1.y);
	} else {
		if (p1.y < p2.y) {
			printf("%lf %lf\n%lf %lf\n", p1.x, p1.y, p2.x, p2.y);
		} else {
			printf("%lf %lf\n%lf %lf\n", p2.x, p2.y, p1.x, p1.y);
		}
	}
	printf("\n");
}

void showDanger(Danger *ds, int n) {
	for (int i=0; i < n; i++)
		printf("%lf (%lf, %lf) (%lf, %lf)\n", ds[i].distance, ds[i].p1.x, ds[i].p1.y, ds[i].p2.x, ds[i].p2.y);
}