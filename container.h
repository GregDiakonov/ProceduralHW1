#ifndef CONTAINER_H
#define CONTAINER_H
#define MAX_LENGTH 10000
#include "vehicle.h"
#include "stdlib.h"

// Длина контейнера часто используется в методах.
// Снабжение массива данных массивом указателей на эти данные также удобно.
struct container {
	int length;
	vehicle arr[MAX_LENGTH];
    vehicle* pointer_arr[MAX_LENGTH];
};

int CountLinesNumber(FILE* file);

void Initialize(container* container);

vehicle ParseDataString(char* string);

void Input(container* container, FILE* file);

container InputRandom(container* container, int size);

#endif