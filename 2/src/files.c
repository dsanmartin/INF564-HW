#include <stdio.h>
#include <stdlib.h>
#include "include/files.h"
#include "include/list.h"

void readInput(Node **head) {
	int id = 0, n = 0;
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
	}
}

void showDanger(Danger *ds, int n) {
	for (int i=0; i < n; i++)
		printf("%lf (%lf, %lf) (%lf, %lf)\n", ds[i].distance, ds[i].p1.x, ds[i].p1.y, ds[i].p2.x, ds[i].p2.y);
}