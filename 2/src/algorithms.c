#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

int smallX(Point p1, Point p2) {
	return p1.x < p2.x;
}

int smallY(Point p1, Point p2) {
	return p1.y < p2.y;
}

int lessThan(int x, int y) {
	return x < y;
}

void swap(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void swapPoint(Point *p, int i, int j) {
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
		swapPoint(p, l, r);
	} while (l < r);
	return l; // retorna la primera posición en la partición de la derecha
}

void quickSort(Point *p, int l, int r, int (*compare)(Point, Point)) {
	int posPivot, k;
	if (r <= l) return; // Arreglo de tamaño 0 o 1, no hace falta ordenar
	posPivot = findPivot(l, r);
	swapPoint(p, posPivot, r); // intercambia pivote con el último elemento
	k = partition(p, l-1, r, r, *compare);
	swapPoint(p, k, r); // intercambia pivote con primer elemento partición derecha
	quickSort(p, l, k-1, *compare);
	quickSort(p, k+1, r, *compare);
}

void insertionSort(int *A, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; (j > 0) && (lessThan(A[j], A[j-1])); j--)
			swap(A, j, j-1);
}

Danger bruteForce(Point *p, int n) {
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
	Danger d, dl, dr;
	// If there are 2 or 3 points, then use brute force 
	if (n <= 3) 
		return bruteForce(p, n); 

	// Find the middle point 
	int mid = n/2; 
	Point midPoint = p[mid]; 

	// Consider the vertical line passing through the middle point 
	// calculate the smallest distance dl on left of middle point and 
	// dr on right side 
	
	dl = closestUtilD(p, mid); 
	dr = closestUtilD(p + mid, n-mid); 

	// Find the smaller of two distances 
	d = minD(dl, dr); 

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

Danger divide(Point *Px, Point *Py, int n) {
	Danger d, d_l, d_r; // Structure to save closest pair

	/* If there is only one point */
	if (n <= 3)
		return bruteForce(Px, n); 
		
	/* Compute midpoint */
	int mid = n / 2;
	Point mid_point = Py[mid];

	/* Recursively search closest point in each division */
	d_l = divide(Px, Py, mid);
	d_r = divide(Px + mid, Py + mid, n - mid);

	/* Compare which is the closes pair on point of each division */
	if (d_l.distance < d_r.distance) 
		d = d_l;
	else
		d = d_r;

	/* Search points bewtween division with smaller distance than min distance computed above */
	Point *strip = (Point *) malloc(n * sizeof(Point));
	int k = 0; 
	for (int i = 0; i < n; i++) 
		if (fabs(Py[i].x - mid_point.x) < d.distance) 
			strip[k] = Py[i], k++; 
	
	/* Sort strip points according to y coordinate */
	//quickSort(strip, 0, k - 1, smallY);  

	// Pick all points one by one and try the next points till the difference 
	// between y coordinates is smaller than d. 
	// This is a proven fact that this loop runs at most 6 times
	double dist;
	for (int i = 0; i < k; ++i) {
		for (int j = i+1; j < k && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d.distance * d.distance; ++j) {
			dist = euclidean(strip[i], strip[j]);
			if (dist < d.distance) {
				d.distance = dist;
				d.p1 = strip[i];
				d.p2 = strip[j];
			}
		}
	}

	return d;
}

Danger closestPair(Point *p, int n) {
	//Danger d;
	Point *Px, *Py;
	Px = (Point *) malloc(n * sizeof(Point));
	Py = (Point *) malloc(n * sizeof(Point));
	memcpy(Px, p, n * sizeof(Point));
	memcpy(Py, p, n * sizeof(Point));

	/*  Sort points by x coordinate */
	quickSort(Px, 0, n - 1, smallX);
	quickSort(Py, 0, n - 1, smallY);

	// for (int i = 0; i < n; i++) {
	// 	printf("p: %lf %lf\n", p[i].x, p[i].y);
	// 	printf("px: %lf %lf\n", Px[i].x, Px[i].y);
	// 	printf("py: %lf %lf\n", Py[i].x, Py[i].y);
	// }
		

	/* Divide and Conquer */
	return divide(Px, Py, n);
}