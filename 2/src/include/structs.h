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

struct danger {
	double distance;
	Point p1;
	Point p2;
} typedef Danger;

#endif