#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

int findPivot(int l, int r);
int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point));
int smallX(Point p1, Point p2);
int smallY(Point p1, Point p2);
double euclidean(Point p1, Point p2);
void swap(Point *p, int i, int j);
void quickSort(Point *p, int l, int r, int (*compare)(Point, Point));
Danger bruteForce(Point *p, int n);
Danger closestPair(Point *p, int n);
Danger divideAndConquer(Point *Px, Point *Py, int n);

#endif