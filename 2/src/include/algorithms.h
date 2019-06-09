#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

int findPivot(int l, int r);
int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point));
int smaller(Danger d1, Danger d2);
double euclidean(Point p1, Point p2);
void swap(Point *p, int i, int j);
void quickSort(Point *p, int l, int r, int (*compare)(Point, Point));
void insertionSort(int *A, int n);
Danger bruteForceD(Point *p, int n);
Danger closestD(Point *p, int n);

// double stripClosest(Point *p, int n, float d);
// double bruteForce(Point *p, int n);
// Danger prop(Point *p, int n);
// void min(Point *p, double *M, int n);
// void mergeSort(Danger *A, Danger *temp, int izq, int der);
// void distances(Point *points, int n);
// void distanceMatrix(Point *p, double *M, int n);
// void bubbleSort(Danger *ds, int n);
// void selectionSort(Danger *ds, int n);
// int searchMin(Danger *ds, int n);
// double closest(Point *p, int n);

#endif