#include "vehicle.h"

ship InputRandomShip() {
    int tonnage = rand() % 10000;
    int ship_type = rand() % 3;
    ship new_ship;
    new_ship.tonnage = tonnage + 1;
    if(ship_type==0) {
        new_ship.ship_type = LINER;
    }
    if(ship_type==1) {
        new_ship.ship_type = TUGBOAT;
    }
    if(ship_type==2) {
        new_ship.ship_type = TANKER;
    }
    return new_ship;
}

void RawOutput(ship* ship, FILE* file) {
    fprintf(file, " %d ", ship->tonnage);
    if(ship->ship_type==LINER) {
        fprintf(file, "1");
    }
    if(ship->ship_type==TUGBOAT) {
        fprintf(file, "2");
    }
    if(ship->ship_type==TANKER) {
        fprintf(file, "3");
    }
    return;
}

void Output(ship* ship, FILE* file) {
    fprintf(file, "Tonnage: %d\n", ship->tonnage);
    if(ship->ship_type == TANKER) {
        fprintf(file,"Type: %s\n", "Tanker");
    }
    if(ship->ship_type == TUGBOAT) {
        fprintf(file, "Type: %s\n", "Tugboat");
    }
    if(ship->ship_type == LINER) {
        fprintf(file, "Type: %s\n", "Liner");
    }
}

