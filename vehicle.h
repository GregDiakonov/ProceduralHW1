#ifndef VEHICLE_H
#define VEHICLE_H

#include "plane.h"
#include "train.h"
#include "ship.h"
#include "time.h"
#include "stdlib.h"

enum type_flag {
    PLANE=0,
    TRAIN=1,
    SHIP=2
};

// Структура транспортного средства.
// Тут даны общие для всех средств параметры.
// И объединение, в себе информацию о более сложном транспортном средстве.
// В объектах train, ship и plane хранится только особые данные для этих видов ТС.
struct vehicle {
	int speed;
	double way_length;
    double ideal_time;
    type_flag flag;
	union {
		plane p;
		train t;
		ship s;
	};
};

vehicle InputRandom();

void RawOutput(vehicle* vehicle, FILE* file);

void Output(vehicle* vehicle, FILE* file);

#endif
