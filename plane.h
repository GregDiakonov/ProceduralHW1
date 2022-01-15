#ifndef PLANE_H
#define PLANE_H

#include <stdio.h>

struct plane {
	int flight_radius;
	int capacity;
};

plane InputRandomPlane();

void RawOutput(plane* plane, FILE* file);

void Output(plane* plane, FILE* file);

#endif
