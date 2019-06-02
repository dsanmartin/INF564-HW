#include <stdio.h>
#include <math.h>
#include "include/algorithms.h"

int smaller(Danger d1, Danger d2) {
	return d1.distance < d2.distance;
}

void swap(Danger *d, int i, int j) {
	Danger temp = d[i];
	d[i] = d[j];
	d[j] = temp;
}

void bubbleSort(Danger *ds, int n) {
	for (int i = 0; i < n-1; i++)
		for (int j = n - 1; j > i; j--)
			if (smaller(ds[j], ds[j-1]))
				swap(ds, j, j-1);
}

void selectionSort(Danger *ds, int n) {
	int i, j, min;
	for (i = 0; i < n-1; i++) {
		min = i;
		for (j = n-1; j > i; j--)
			if (smaller(ds[j], ds[min])) min = j;
			swap(ds, i, min);
	}
}

void mergeSort(Danger *A, Danger *temp, int izq, int der) {
	int i, i1, i2, med = (izq + der) / 2;
	if (izq == der) return;
	mergeSort(A, temp, izq, med);
	mergeSort(A, temp, med+1, der);
	for (i = izq; i <= der; i++) temp[i] = A[i];
	i1 = izq; i2 = med + 1;
	for (i = izq; i <= der; i++) {
		if (i1 == med + 1) A[i] = temp[i2++];
		else if (i2 > der) A[i] = temp[i1++];
		else if (smaller(temp[i1], temp[i2])) A[i] = temp[i1++];
		else A[i] = temp[i2++];
	}
}

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

void warningFlights(Danger *flights, Point *p, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			flights[j * n + i].distance = euclidean(p[i], p[j]);
			flights[j * n + i].p1 = p[i];
			flights[j * n + i].p2 = p[j];
			if (i == j) {
				flights[j * n + i].distance = INFINITY;
				flights[j * n + i].p1 = p[i];
				flights[j * n + i].p2 = p[j];
			} 
		}
	}
}