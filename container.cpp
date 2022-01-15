#include "container.h"
#include <string.h>
#include <stdlib.h>

// Инициализация контейнера.
void Initialize(container* container) {
	container->length = 0;
    for(int i=0; i<MAX_LENGTH; i++) {
        container->pointer_arr[i] = &(container->arr[i]);
    }
}

/*
 * МЕТОДЫ ЗАПОЛНЕНИЯ КОНТЕЙНЕРА.
 */

// Этот метод читает файл ввода построчно, на основе информации из строк он заполняет контейнер.
void Input(container* container, FILE* file) {
	file = fopen("input.txt", "r");
    int lines_number = CountLinesNumber(file);
    for(int i=0; i<=lines_number; i++) {
        char* new_line = (char*)malloc(MAX_LENGTH);
        new_line = fgets(new_line, MAX_LENGTH, file);
        vehicle new_vehicle = ParseDataString(new_line);
        if(new_vehicle.speed == -1) {
            printf("Some of the provided data was unsuitable for creating a proper vehicle!\n");
            continue;
        }
        container->arr[i] = new_vehicle;
        ++container->length;
        free(new_line);
    }
	fclose(file);
}

// Этот метод анализирует содержимое считанной из вводного файла строки.
// Длинный, но простой. Его длина обусловлена количеством данных и обработкой ошибок.
vehicle ParseDataString(char* string) {
    int data_number=0;
    vehicle new_vehicle;
    char* new_token = strtok(string, " ");
    while(new_token != NULL) {
        if(data_number==0) {
            if(strcmp(new_token, "Ship")==0) {
                ship new_ship;
                new_vehicle.s = new_ship;
                new_vehicle.flag = SHIP;
            }
            else if(strcmp(new_token, "Plane")==0) {
                plane new_plane;
                new_vehicle.p = new_plane;
                new_vehicle.flag = PLANE;
            }
            else if(strcmp(new_token, "Train")==0) {
                train new_train;
                new_vehicle.t = new_train;
                new_vehicle.flag = TRAIN;
            }
            else {
                new_vehicle.speed = -1;
                return new_vehicle;
            }
        }
        if(data_number==1) {
            new_vehicle.speed = atoi(new_token);
            if(new_vehicle.speed<=0) {
                new_vehicle.speed=-1;
                return new_vehicle;
            }
        }
        if(data_number==2) {
            new_vehicle.way_length = atof(new_token);
            if(new_vehicle.way_length<=0) {
                new_vehicle.speed=-1;
                return new_vehicle;
            }
        }
        if(data_number == 3) {
            if(new_vehicle.flag == PLANE) {
                new_vehicle.p.flight_radius = atoi(new_token);
                if(new_vehicle.p.flight_radius<=0) {
                    new_vehicle.speed=-1;
                    return new_vehicle;
                }
            }
            if(new_vehicle.flag == TRAIN) {
                new_vehicle.t.wagon_number = atoi(new_token);
                if(new_vehicle.t.wagon_number<=0) {
                    new_vehicle.speed=-1;
                    return new_vehicle;
                }
            }
            if(new_vehicle.flag == SHIP) {
                new_vehicle.s.tonnage = atoi(new_token);
                if(new_vehicle.s.tonnage<=0) {
                    new_vehicle.speed=-1;
                    return new_vehicle;
                }
            }
        }
        if(data_number == 4) {
            if(new_vehicle.flag == PLANE) {
                new_vehicle.p.capacity = atoi(new_token);
                if(new_vehicle.p.capacity<=0) {
                    new_vehicle.speed=-1;
                    return new_vehicle;
                }
            }
            if(new_vehicle.flag == SHIP) {
                new_vehicle.s.ship_type = (SHIP_TYPE)atoi(new_token);
                if(atoi(new_token)<=0 || atoi(new_token) >= 4) {
                    new_vehicle.speed=-1;
                    return new_vehicle;
                }
            }
        }
        new_token = strtok(NULL, " ");
        ++data_number;
    }
    return new_vehicle;
}

// Аналог метода Input, но для случайной генерации транспортных средств.
container InputRandom(container* container, int size) {
    for(int i=0; i<size; i++) {
        vehicle new_vehicle = InputRandom();
        container->arr[i] = new_vehicle;
    }
    container->length = size;
    return *container;
}

/*
 * ДОПОЛНИТЕЛЬНОЕ
 */

// Метод подсчитывает количество строк в файле.
// Он делает это не очень точно, но пустые и неправильные строки будут не прочитаны без проблем для исполнения.
int CountLinesNumber(FILE* file) {
    int answer=0;
    char next_character=fgetc(file);
    while(next_character!=EOF) {
        if(next_character == '\n' || next_character == '\0') {
            ++answer;
        }
        next_character= fgetc(file);
    }
    rewind(file);
    return answer;
}