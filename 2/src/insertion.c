#include <stdio.h>
#include <stdlib.h>


/* Professor Arroyuelo's class notes implementation */
void swap(int *A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

void insertionSort(int *A, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; (j > 0) && (A[j-1] > A[j]); j--)
			swap(A, j, j-1);
}

/* Write swap function inline */
void isort2(int *A, int n) { 
	int tmp;
 	for (int i = 1; i < n; i++)
 		for (int j = i; j > 0 && A[j-1] > A[j]; j--) {
 			tmp = A[j];
 			A[j] = A[j-1];
 			A[j-1] = tmp;
 		}
}

/* Remove swap to avoid create temporary variable in each backward pass */
void insertionSortOPT1(int *A, int n) { 
	int i, j, tmp;
	for (i = 1; i < n; i++) {
		tmp = A[i];
		for (j = i; j > 0 && A[j-1] > tmp; j--)
			A[j] = A[j-1];
		A[j] = tmp;
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

/* Show Array */
void showArray(int *A, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", A[i]);
	}
}


int main(int argc, char **argv) {
	int n = 0, opt = 0;
	int *A;

	if (argc < 2) {
		printf("Arguments:\nOPT: Algorithm used.\nN: Number array's elements.\n");
		return EXIT_FAILURE;
	} else {
		opt = atoi(argv[1]);
		n = atoi(argv[2]);
	}

	A = (int *) malloc(n * sizeof(int));
	createInput(A, n); // Fill random array

	switch (opt) {
		case 0:
			insertionSort(A, n);
			break;
		case 1:
			insertionSortOPT1(A, n);
			break;
		default:
			insertionSort(A, n);
			break;
	}

 	// showArray(A, n);

	return 0;
}

	/* 
	int t1[17] = {8, 9, 10, 11, 12, 3, 4, 5, 18, 19, 20, 16, 17, 13, 14, 15, 16};
	int t2[16] = {8, 11, 15, 16, 3, 4, 5, 18, 20, 21, 25, 26, 27, 7, 10, 14};
	int t3[19] = {8, 11, 15, 16, 19, 5, 4, 3, 1, 27, 23, 21, 20, 18, 17, 13, 14, 22, 24};

	showArray(t1, 17);
	showArray(t2, 16);
	showArray(t3, 19);

	insertionSort(t1, 17);
	insertionSort(t2, 16);
	insertionSort(t3, 19);

	showArray(t1, 17);
	showArray(t2, 16);
	showArray(t3, 19);
	*/