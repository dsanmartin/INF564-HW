#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

int findPivot(int l, int r);
int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point));
double euclidean(Point p1, Point p2);
void swap(int *a, int i, int j);
void swapPoint(Point *p, int i, int j);
void quickSort(Point *p, int l, int r, int (*compare)(Point, Point));
void insertionSort(int *A, int n);
Danger bruteForce(Point *p, int n);
Danger closestD(Point *p, int n);
Danger closestPair(Point *p, int n);

#endif