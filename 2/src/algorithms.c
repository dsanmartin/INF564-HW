#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/algorithms.h"
#include "include/files.h"

/* Compute Euclidean distance */
double euclidean(Point p1, Point p2) {
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double min(double x, double y) { 
	return (x < y) ? x : y; 
}

Danger minD(Danger d1, Danger d2) {
	return (d1.distance < d2.distance) ? d1 : d2;
}

int smaller(Danger d1, Danger d2) {
	return d1.distance < d2.distance;
}

int smallX(Point p1, Point p2) {
	return p1.x < p2.x;
}

int smallY(Point p1, Point p2) {
	return p1.y < p2.y;
}

int lessThan(int x, int y) {
	return x < y;
}

void swap(Point *p, int i, int j) {
	Point tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
}

int findPivot(int l, int r) {
	return (l + r) / 2;
}

int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point)) {
	do {
		while ((*compare)(p[++l], p[posPivot]));
		while ((l < r) && (*compare)(p[posPivot], p[--r]));
		swap(p, l, r);
	} while (l < r);
	return l; // retorna la primera posición en la partición de la derecha
}

void quickSort(Point *p, int l, int r, int (*compare)(Point, Point)) {
	int posPivot, k;
	if (r <= l) return; // Arreglo de tamaño 0 o 1, no hace falta ordenar
	posPivot = findPivot(l, r);
	swap(p, posPivot, r); // intercambia pivote con el último elemento
	k = partition(p, l-1, r, r, *compare);
	swap(p, k, r); // intercambia pivote con primer elemento partición derecha
	quickSort(p, l, k-1, *compare);
	quickSort(p, k+1, r, *compare);
}

// void bubbleSort(Danger *ds, int n) {
// 	for (int i = 0; i < n-1; i++)
// 		for (int j = n - 1; j > i; j--)
// 			if (smaller(ds[j], ds[j-1]))
// 				swap(ds, j, j-1);
// }

// void selectionSort(Danger *ds, int n) {
// 	int i, j, min;
// 	for (i = 0; i < n-1; i++) {
// 		min = i;
// 		for (j = n-1; j > i; j--)
// 			if (smaller(ds[j], ds[min])) min = j;
// 			swap(ds, i, min);
// 	}
// }

// void mergeSort(Danger *A, Danger *temp, int izq, int der) {
// 	int i, i1, i2, med = (izq + der) / 2;
// 	if (izq == der) return;
// 	mergeSort(A, temp, izq, med);
// 	mergeSort(A, temp, med+1, der);
// 	for (i = izq; i <= der; i++) temp[i] = A[i];
// 	i1 = izq; i2 = med + 1;
// 	for (i = izq; i <= der; i++) {
// 		if (i1 == med + 1) A[i] = temp[i2++];
// 		else if (i2 > der) A[i] = temp[i1++];
// 		else if (smaller(temp[i1], temp[i2])) A[i] = temp[i1++];
// 		else A[i] = temp[i2++];
// 	}
// }

// Danger linearMin(Point *p, int n) {
// 	Danger dg;
// 	int i_min = 1;
// 	double min = INFINITY, dist;
// 	for (int i=1; i < n; i++) {
// 		dist = euclidean(p[i], p[i-1]);
// 		if (dist < min) {
// 			min = dist;
// 			i_min = i;
// 		}
// 	}

// 	dg.distance = min;
// 	dg.p1 = p[i_min-1];
// 	dg.p2 = p[i_min];
// 	return dg;
// }

// double bruteForce(Point *p, int n) {
// 	double min = INFINITY, d;
// 	int i_min, j_min; // To save minimum positions
// 	for (int i = 0; i < n; i++) {
// 		for (int j = i + 1; j < n; j++) {
// 			d = euclidean(p[i], p[j]);
// 			if (d < min) {
// 				min = d;
// 				i_min = i;
// 				j_min = j;
// 			}
// 		}
// 	}
// 	//printf("Min: %f\n", min);
// 	//showPoints(p[i_min], p[j_min]);
// 	return min;
// }

Danger bruteForceD(Point *p, int n) {
	double min = INFINITY, d;
	int i_min, j_min; // To save minimum positions
	Danger dn;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			d = euclidean(p[i], p[j]);
			if (d < min) {
				min = d;
				i_min = i;
				j_min = j;
			}
		}
	}
	dn.distance = min;
	dn.p1 = p[i_min];
	dn.p2 = p[j_min];
	return dn;
}

// /* Divide and conquer */
// double stripClosest(Point *p, int n, float d) { 
// 	double min = d;  // Initialize the minimum distance as d 

// 	quickSort(p, 0, n - 1, smallY);  

// 	// Pick all points one by one and try the next points till the difference 
// 	// between y coordinates is smaller than d. 
// 	// This is a proven fact that this loop runs at most 6 times 
// 	for (int i = 0; i < n; ++i) 
// 		for (int j = i+1; j < n && (p[j].y - p[i].y) < min; ++j) 
// 			if (euclidean(p[i], p[j]) < min) 
// 				min = euclidean(p[i], p[j]); 

// 	return min; 
// }

// // A recursive function to find the smallest distance. The array P contains 
// // all points sorted according to x coordinate 
// double closestUtil(Point *p, int n)  { 
// 	// If there are 2 or 3 points, then use brute force 
// 	if (n <= 3) 
// 		return bruteForce(p, n); 

// 	// Find the middle point 
// 	int mid = n/2; 
// 	//printf("mid: %d\n", mid);
// 	Point midPoint = p[mid]; 

// 	// Consider the vertical line passing through the middle point 
// 	// calculate the smallest distance dl on left of middle point and 
// 	// dr on right side 
	
// 	double dl = closestUtil(p, mid); 
// 	double dr = closestUtil(p + mid, n-mid); 

// 	// Find the smaller of two distances 
// 	double d = min(dl, dr); 

// 	// Build an array strip[] that contains points close (closer than d) 
// 	// to the line passing through the middle point 
// 	Point *strip = (Point *) malloc(n * sizeof(Point));//strip[n]; 
// 	int j = 0; 
// 	for (int i = 0; i < n; i++) 
// 		if (fabs(p[i].x - midPoint.x) < d) 
// 			strip[j] = p[i], j++; 

// 	// Find the closest points in strip.  Return the minimum of d and closest 
// 	// distance is strip[] 
// 	return min(d, stripClosest(strip, j, d)); 
// } 
	
// // The main functin that finds the smallest distance 
// // This method mainly uses closestUtil() 
// double closest(Point *p, int n)  { 
// 		quickSort(p, 0, n - 1, smallX);
// 		// Use recursive function closestUtil() to find the smallest distance 
// 		return closestUtil(p, n); 
// }

Danger stripClosestD(Point *p, int n, Danger d) { 
	double min = d.distance;  // Initialize the minimum distance as d 
	Danger dg;
	dg.distance = min;
	dg.p1 = d.p1;
	dg.p2 = d.p2;

	quickSort(p, 0, n - 1, smallY);  

	// Pick all points one by one and try the next points till the difference 
	// between y coordinates is smaller than d. 
	// This is a proven fact that this loop runs at most 6 times 
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n && (p[j].y - p[i].y) < min; ++j) {
			if (euclidean(p[i], p[j]) < min) {
				dg.distance = euclidean(p[i], p[j]); 
				dg.p1 = p[i];
				dg.p2 = p[j];
			}
		}
	}
	return dg; 
}

// A recursive function to find the smallest distance. The array P contains 
// all points sorted according to x coordinate 
Danger closestUtilD(Point *p, int n)  { 
	Danger dg, dl, dr, ds;
	// If there are 2 or 3 points, then use brute force 
	if (n <= 3) 
		return bruteForceD(p, n); 

	// Find the middle point 
	int mid = n/2; 
	Point midPoint = p[mid]; 

	// Consider the vertical line passing through the middle point 
	// calculate the smallest distance dl on left of middle point and 
	// dr on right side 
	
	dl = closestUtilD(p, mid); 
	dr = closestUtilD(p + mid, n-mid); 

	// Find the smaller of two distances 
	Danger d = minD(dl, dr); 

	// Build an array strip[] that contains points close (closer than d) 
	// to the line passing through the middle point 
	Point *strip = (Point *) malloc(n * sizeof(Point));//strip[n]; 
	int j = 0; 
	for (int i = 0; i < n; i++) 
		if (fabs(p[i].x - midPoint.x) < d.distance) 
			strip[j] = p[i], j++; 

	return minD(d, stripClosestD(strip, j, d));
} 
	
// The main functin that finds the smallest distance 
// This method mainly uses closestUtil() 
Danger closestD(Point *p, int n)  { 
		quickSort(p, 0, n - 1, smallX);
		// Use recursive function closestUtil() to find the smallest distance 
		return closestUtilD(p, n); 
}


void insertionSort(int *A, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; (j > 0) && (lessThan(A[j], A[j-1])); j--)
			swap(A, j, j-1);
}


// Danger prop(Point *p, int n) {
// 	quickSort(p, 0, n - 1, smallX);
// 	quickSort(p, 0, n - 1, smallY);
// 	return linearMin(p, n);
// }

