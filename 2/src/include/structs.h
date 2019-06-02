#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct point {
	double x;
	double y;
} Point;

typedef struct flights {
	int id;
	int n;
	Point *points;
} Flights;

typedef struct node {
	Flights data;
	struct node* next;
} Node;

typedef struct danger {
	double distance;
	Point p1;
	Point p2;
} Danger;

#endif