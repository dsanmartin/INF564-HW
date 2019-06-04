#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

int smaller(Danger d1, Danger d2);
int searchMin(Danger *ds, int n);
int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point));
int findPivot(int l, int r);
double stripClosest(Point *p, int n, float d);
double bruteForce(Point *p, int n);
Danger bruteForceD(Point *p, int n);
int DACMin(Danger *ds, int l, int r);
int binarySearch(Danger *ds, int l, int r, double min);
void swap(Point *p, int i, int j);
void bubbleSort(Danger *ds, int n);
void selectionSort(Danger *ds, int n);
void mergeSort(Danger *A, Danger *temp, int izq, int der);
void quickSort(Point *p, int l, int r, int (*compare)(Point, Point));
double euclidean(Point p1, Point p2);
void distances(Point *points, int n);
void distanceMatrix(Point *p, double *M, int n);
void insertionSort(int *A, int n);
//void min(Point *p, double *M, int n);
double closest(Point *p, int n);
Danger closestD(Point *p, int n);
double min(double x, double y);
void warningFlights(Danger *flights, Point *p, int n);
void warningFlightsOPT(Danger *flights, Point *p, int n);

#endif