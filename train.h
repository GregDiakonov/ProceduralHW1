#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>

struct train {
	int wagon_number;
};

train InputRandomTrain();

void RawOutput(train* train, FILE* file);

void Output(train* train, FILE* file);

#endif
