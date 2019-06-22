#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libsort.c"

/* Professor Arroyuelo's class notes implementation */
void swap(int *A, int i, int j) {
	int a = A[i];
	A[i] = A[j];
	A[j] = a;
}

/* Binary search to find an element's position */
int binarySearch(int *A, int a, int l, int r) { 
	if (r <= l) 
		return (a > A[l]) ? (l + 1) : l; 

	int m = (l + r) / 2; 

	if (a == A[m]) 
		return m + 1; 

	if(a > A[m]) 
		return binarySearch(A, a, m + 1, r); 

	return binarySearch(A, a, l, r - 1); 
} 

void insertionSort(int *A, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; (j > 0) && (A[j-1] > A[j]); j--)
			swap(A, j, j-1);
}

/* Remove swap to avoid create temporary variable in each 'insertion' */
void insertionSortOPT1(int *A, int n) { 
	int i, j, a;
	for (i = 1; i < n; i++) {
		a = A[i];
		for (j = i; j > 0 && A[j-1] > a; j--)
			A[j] = A[j-1];
		A[j] = a;
	}
}

/* Recursive version */
void insertionSortOPT2(int *A, int n) {
	if (n > 0) {
		insertionSortOPT2(A, n-1);
		int a = A[n];
		int j = n ;
		while (j > 0 && A[j-1] > a) {
			A[j] = A[j-1];
			j--;
		}
		A[j] = a;
	}
}

/* Jump sorted elements */
void insertionSortOPT3(int *A, int n) { 
	int i, j, a;
	for (i = 1; i < n; i++) {
		while (A[i-1] < A[i] && i < n - 1) i++; /* Pass sorted elements */
		a = A[i];
		for (j = i; j > 0 && A[j-1] > a; j--)
			A[j] = A[j-1];
		A[j] = a;
	}
}

void insertionSortOPT4(int *A, int n) { 
  int i, j, a, pos; 
  for (i = 1; i < n; ++i) { 
		j = i - 1; 
		a = A[i]; 

		// Position to insert the temporal value
		pos = binarySearch(A, a, 0, j); 

		// Move elements
		while (j >= pos) { 
			A[j+1] = A[j]; 
			j--; 
		} 
		A[pos] = a; 
	}	 
} 

/* Utils */

/* Random integer array  for testing */
void createInput(int *A, int n) {
	srand(666);
	int lower = 0, upper = 10000;
	for (int i = 0; i < n; i++) {
		A[i] = (rand() % (upper - lower + 1)) + lower;; 
	}
}

/* Load data for benchmark */
void loadData(int *A, int n) {
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
}

/* Show Array */
void showArray(int *A, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", A[i]);
	}
	printf("\n");
}


int main(int argc, char **argv) {
	int n = 0, opt = 0;
	int *A;

	if (argc < 2) {
		printf("USE: ./insertion OPT N\nOPT: Algorithm version used.\nN: Number of array's elements.\n");
		return EXIT_FAILURE;
	} else {
		opt = atoi(argv[1]);
		n = atoi(argv[2]);
	}

	A = (int *) malloc(n * sizeof(int));

	loadData(A, n);

	switch (opt) {
		case 0:
			insertionSort(A, n);
			break;
		case 1:
			insertionSortOPT1(A, n);
			break;
		case 2:
			insertionSortOPT2(A, n);
			break;
		case 3:
			insertionSortOPT3(A, n);
			break;
		case 4:
			insertionSortOPT4(A, n);
			break;
		case 5:
			librarySort(A, n);
			break;
		default:
			insertionSort(A, n);
			break;
	}

	return 0;
}