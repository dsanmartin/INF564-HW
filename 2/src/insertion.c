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

		// find location where selected sould be inseretd 
		pos = binarySearch(A, a, 0, j); 

		// Move all elements after location to create space 
		while (j >= pos) { 
			A[j+1] = A[j]; 
			j--; 
		} 
		A[pos] = a; 
	}	 
} 

/* Utils */

/* Random integer array */
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
	//createInput(A, n); // Fill random array
	loadData(A, n);

	//showArray(A, n);

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

	//showArray(A, n);

	return 0;
}

// int main(int argc, char **argv) {

// 	int opt = atoi(argv[1]);

// 	int t1[17] = {8, 9, 10, 11, 12, 3, 4, 5, 18, 19, 20, 16, 17, 13, 14, 15, 16};
// 	int t2[16] = {8, 11, 15, 16, 3, 4, 5, 18, 20, 21, 25, 26, 27, 7, 10, 14};
// 	int t3[19] = {8, 11, 15, 16, 19, 5, 4, 3, 1, 27, 23, 21, 20, 18, 17, 13, 14, 22, 24};

// 	showArray(t1, 17);
// 	// showArray(t2, 16);
// 	// showArray(t3, 19);

// 	if (opt == 0) {
// 		insertionSort(t1, 17);
// 		insertionSort(t2, 16);
// 		insertionSort(t3, 19);
// 	} else if (opt == 1) {
// 		insertionSortOPT1(t1, 17);
// 		insertionSortOPT1(t2, 16);
// 		insertionSortOPT1(t3, 19);
// 	} else if (opt == 2) {
// 		insertionSortOPT2(t1, 17);
// 		insertionSortOPT2(t2, 16);
// 		insertionSortOPT2(t3, 19);
// 	} else if (opt == 3) {
// 		insertionSortOPT3(t1, 17);
// 		// insertionSortOPT3(t2, 16);
// 		// insertionSortOPT3(t3, 19);
// 	} else {
// 		printf("Error OPT");
// 		return EXIT_FAILURE;
// 	}

// 	showArray(t1, 17);
// 	// showArray(t2, 16);
// 	// showArray(t3, 19);

// 	// printf("%d\n", binarySearch(t1, 0, 16, 20));
// 	// printf("%d\n", binarySearch(t2, 0, 15, 100));
// 	// printf("%d\n\n", binarySearch(t3, 0, 18, 16));


// 	return 0;
// }