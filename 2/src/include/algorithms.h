#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

int smaller(Danger d1, Danger d2);
void swap(Danger *d, int i, int j);
void bubbleSort(Danger *ds, int n);
void selectionSort(Danger *ds, int n);
void mergeSort(Danger *A, Danger *temp, int izq, int der);
double euclidean(Point p1, Point p2);
void distances(Point *points, int n);
void distanceMatrix(Point *p, double *M, int n);
void min(Point *p, double *M, int n);
void warningFlights(Danger *flights, Point *p, int n);
void warningFlightsOPT(Danger *flights, Point *p, int n);

#endif