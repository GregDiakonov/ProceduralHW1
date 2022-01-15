#include "vehicle.h"

train InputRandomTrain() {
    int wagon_number = rand() % 30;
    train new_train;
    new_train.wagon_number = wagon_number+1;
    return new_train;
}

void RawOutput(train* train, FILE* file) {
    fprintf(file, " %d", train->wagon_number);
    return;
}

void Output(train* train, FILE* file) {
    fprintf(file, "Wagon number: %d\n", train->wagon_number);
}

