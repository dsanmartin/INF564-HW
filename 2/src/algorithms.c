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

/* Comparison function for sort algorithm (x-coordinate) */
int smallX(Point p1, Point p2) {
	return p1.x < p2.x;
}

/* Comparison function for sort algorithm (y-coordinate) */
int smallY(Point p1, Point p2) {
	return p1.y < p2.y;
}

/* Swap function */
void swap(Point *p, int i, int j) {
	Point tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
}

/* Find pivot for QuickSort */
int findPivot(int l, int r) {
	return (l + r) / 2;
}

/* Partition function for QuickSort */
int partition(Point *p, int l, int r, int posPivot, int (*compare)(Point, Point)) {
	do {
		while ((*compare)(p[++l], p[posPivot]));
		while ((l < r) && (*compare)(p[posPivot], p[--r]));
		swap(p, l, r);
	} while (l < r);
	return l; 
}

/* Quick Sort taken from class notes */
void quickSort(Point *p, int l, int r, int (*compare)(Point, Point)) {
	int posPivot, k;
	if (r <= l) return;
	posPivot = findPivot(l, r);
	swap(p, posPivot, r);
	k = partition(p, l-1, r, r, *compare);
	swap(p, k, r); 
	quickSort(p, l, k-1, *compare);
	quickSort(p, k+1, r, *compare);
}

/* Brute force approach */
Danger bruteForce(Point *p, int n) {
	double min = INFINITY, d;
	int i_min = 0, j_min = 1; // To save minimum positions
	Danger dn;
	/* Search min distance using distance matrix */
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

/* Divide and conquer */
Danger divideAndConquer(Point *Px, Point *Py, int n) {

	/* If there is 3 or less points, compute by brute force */
	if (n <= 3)
		return bruteForce(Px, n); 
		
	/* Compute midpoint */
	int mid = n / 2;
	Point midpoint = Px[mid];

	/* Divide sorted array (y-axis) */
	Point Py_l[n]; // Sorted array (y-axis) for points at left of vertical line
	Point Py_r[n]; // Sorted array (y-axis) for points at right of vertical line
	int li = 0, ri = 0; // Indexes of left and right Arrays 
	for (int i = 0; i < n; i++) { 
		if (Py[i].x <= midpoint.x) 
			Py_l[li++] = Py[i]; 
		else
			Py_r[ri++] = Py[i]; 
	}

	/* Recursively search closest point in each division */
	Danger d_l = divideAndConquer(Px, Py_l, mid);
	Danger d_r = divideAndConquer(Px + mid, Py_r, n - mid);

	/* Compare which is the closest pair of the divisions */
	Danger d = (d_l.distance < d_r.distance) ? d_l : d_r;

	/* Search points bewtween division with smaller distance than min distance computed above */
	Point *strip = (Point *) malloc(n * sizeof(Point));
	int k = 0; 
	for (int i = 0; i < n; i++) 
		if (fabs(Py[i].x - midpoint.x) < d.distance)
			strip[k] = Py[i], k++; 

	/* Compare point with neighbors. Only keep the points where the difference between y-coordinate is < d */
	double dist;
	for (int i = 0; i < k; ++i) {
		for (int j = i+1; j < k && (strip[j].y - strip[i].y) < d.distance; ++j) {
			dist = euclidean(strip[i], strip[j]);
			if (dist < d.distance) {
				d.distance = dist;
				d.p1 = strip[i];
				d.p2 = strip[j];
			}
		}
	}

	free(strip);

	return d;
}

/* Call closest pair */
Danger closestPair(Point *p, int n) {
	Point *Px, *Py;
	Px = (Point *) malloc(n * sizeof(Point));
	Py = (Point *) malloc(n * sizeof(Point));
	memcpy(Px, p, n * sizeof(Point));
	memcpy(Py, p, n * sizeof(Point));

	/*  Sort points by x and y coordinate */
	quickSort(Px, 0, n - 1, smallX);
	quickSort(Py, 0, n - 1, smallY);

	/* Divide and Conquer */
	return divideAndConquer(Px, Py, n);
}