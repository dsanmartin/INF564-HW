#include <stdio.h>
#include <math.h>
#include "include/algorithms.h"

double euclidean(Point p1, Point p2) {
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

void distances(Point *p, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("(%lf %lf) (%lf %lf) \n", p[i].x, p[i].y, p[j].x, p[j].y);
			printf("%lf\n", euclidean(p[i], p[j]));
		}
	}
}

void distanceMatrix(Point *p, double *M, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M[j * n + i] = euclidean(p[i], p[j]);
			if (i == j) M[j * n + i] = INFINITY;
		}
	}
}

void min(Point *p, double *M, int n) {
	int p1 = 0, p2 = 0;
	double min = INFINITY;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (M[j * n + i] < min) {
				min = M[j * n + i];
				p1 = i;
				p2 = j;
			}
		}
	}
	printf("Min: %lf, p1: (%lf, %lf), p2: (%lf, %lf)\n", min, p[p1].x, p[p1].y, p[p2].x, p[p2].y);
}