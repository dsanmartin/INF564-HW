#include <stdio.h>
#include <stdlib.h>
#include "include/files.h"
#include "include/list.h"

void readInput(Node **head, int *n_flights) {
	int id = 0, n = 0, n_f = 0;
	printf("Reading input...\n");
	while (scanf("%d\n", &n) != EOF) {
		Flights f;
		f.id = id;
		f.n = n;
		f.points = (Point *) malloc(n * sizeof(Point));
		for (int i = 0; i < n; i++) {
			Point p;
			scanf("%lf %lf\n", &p.x, &p.y);
			f.points[i] = p;
		}
		append(head, f);
		id++; // Identifier of flights at same height
		n_f++; // Number of heights
	}
	//n_flights = n_f;
}