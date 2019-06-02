#ifndef STRUCTS_H
#define STRUCTS_H

struct point {
	double x;
	double y;
} typedef Point;

struct flights {
	int id;
	int n;
	Point *points;
} typedef Flights;

typedef struct node {
	Flights data;
	struct node* next;
} Node;

#endif