#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>

enum SHIP_TYPE {
	LINER=1,
	TUGBOAT=2,
	TANKER=3
};

struct ship {
	int tonnage;
	SHIP_TYPE ship_type;
};

ship InputRandomShip();

void RawOutput(ship* ship, FILE* file);

void Output(ship* ship, FILE* file);

#endif
