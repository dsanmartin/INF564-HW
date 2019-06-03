#include <stdio.h>
#include <math.h>
#include "include/algorithms.h"

int smaller(Danger d1, Danger d2) {
	return d1.distance < d2.distance;
}

int searchMin(Danger *ds, int n) {
	int pos = 0;
	double min = ds[pos].distance;
	for (int i = 1; i < n; i++)
		if (ds[i].distance < min) {
			min = ds[i].distance;
			pos = i;
		}
	return pos;
}

int DACMin(Danger *ds, int l, int r) {
	if (l == r)
		return l;
	else {
		int mid = l + (r - l) / 2;
		int l_min = DACMin(ds, l, mid);
		int r_min = DACMin(ds, mid+1, r);
		if (ds[l_min].distance < ds[r_min].distance)
			return l;
		else 
			return r;
	}
	// int mid = l + (r - l ) / 2;

	// if (mid <= 0) {
	// 	return mid;
	// } else {
	// 	int l_min = DACMin(ds, l, mid - 1);
	// 	int r_min = DACMin(ds, mid, r);
	// 	if (ds[l_min].distance < ds[r_min].distance)
	// 		return l_min;
	// 	else
	// 		return r_min;
	// }
}

/*
int binaryMin(Danger *ds, int l, int r, double min) {
	int mid = l + (r - l ) / 2;
	//double min = ds[mid].distance;
	int res;

	if (mid == 0)
		res = mid;

	int l_min = binaryMin(ds, l, mid - 1, min);
	int r_min = binaryMin(ds, mid, r, min);

	if (ds[l_min].distance < min)
		res = l_min;
	else
		res = r_min;
	return res;
	
	// //int pos = 0; // Min position
	// if (r >= l) { 
	// 	int mid = l + (r - l) / 2; 

	// 	if (ds[mid].distance == min) 
  //     return mid;

	// 	// If element is smaller than mid, then 
	// 	// it can only be present in left subarray 
	// 	if (ds[mid].distance > min) 
	// 			return binarySearch(ds, l, mid - 1, min); 

	// 	// Else the element can only be present 
	// 	// in right subarray 
	// 	return binarySearch(ds, mid + 1, r, min); 
  // } 
  
	// // We reach here when element is not 
	// // present in array 
	// //return 0; 
}
*/

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

/* Compute distance between planes. n^2 elements */
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

/* Compute distance between planes, without repeated information. (n^2 - n)/2 elements */
void warningFlightsOPT(Danger *flights, Point *p, int n) {
	int k = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			flights[k].distance = euclidean(p[i], p[j]);
			flights[k].p1 = p[i];
			flights[k].p2 = p[j];
			k++;
		}
	}
}
