#include "vehicle.h"

// Случайный ввод данных о самолёте.
plane InputRandomPlane() {
    int capacity = rand() % 100;
    int flight_radius = rand() % 10000;
    plane new_plane;
    new_plane.capacity = capacity+1;
    new_plane.flight_radius = flight_radius+1;
    return new_plane;
}

void RawOutput(plane* plane, FILE* file) {
    fprintf(file, " %d %d", plane->capacity, plane->flight_radius);
    return;
}

// Вывод особенных данных о самолёте.
void Output(plane* plane, FILE* file) {
    fprintf(file, "Flight Radius: %d\nCapacity: %d\n", plane->flight_radius, plane->capacity);
}

