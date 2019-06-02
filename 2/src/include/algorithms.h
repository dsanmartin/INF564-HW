#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

double euclidean(Point p1, Point p2);
void distances(Point *points, int n);
void distanceMatrix(Point *p, double *M, int n);
void min(Point *p, double *M, int n);

#endif