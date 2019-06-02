#ifndef FILES_H
#define FILES_H

#include "structs.h"

void readInput(Node **head);
void showDanger(Danger *fligths, int n);
void showWarningFlights(Point p1, Point p2);
void saveOutput(const char *filename);

#endif