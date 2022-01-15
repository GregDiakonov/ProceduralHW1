#include "vehicle.h"

/*
 * Ввод случайно сгенерированных данных.
 * 1. Сначала генерируются и записываются общие для каждой машины данные.
 * 2. Затем особенные для каждого типа.
 * 3. Сгенерированное транспортное средство возвращается методом.
 */
vehicle InputRandom() {
    int type = rand() % 3;
    double way_length = rand() % 10000;
    ++way_length;
    vehicle new_vehicle;
    new_vehicle.way_length=way_length;
    if(type==0) {
        int speed = rand() % 1000;
        // Скорость увеличивается на один, чтобы не делить на ноль.
        ++speed;
        new_vehicle.speed=speed;
        new_vehicle.flag = PLANE;
        plane new_plane = InputRandomPlane();
        new_vehicle.p = new_plane;
    }
    if(type==1) {
        int speed = rand() % 100;
        ++speed;
        new_vehicle.speed=speed;
        new_vehicle.flag = TRAIN;
        train new_train = InputRandomTrain();
        new_vehicle.t = new_train;
    }
    if(type==2) {
        int speed = rand() % 50;
        ++speed;
        new_vehicle.speed=speed;
        new_vehicle.flag = SHIP;
        ship new_ship = InputRandomShip();
        new_vehicle.s = new_ship;
    }
    return new_vehicle;
}

// Методы RawOutput пишут информацию не для человека, а для компьютера.
// Они записывают информацию о рандомно сгенерированных данных в вводный файл.
// Чтобы эти данные можно было посмотреть и запустить по-новой.
void RawOutput(vehicle* vehicle, FILE* file) {
    if(vehicle->flag == PLANE) {
        fprintf(file, "Plane %d %lf", vehicle->speed, vehicle->way_length);
        plane* ptr = &vehicle->p;
        RawOutput(ptr, file);
    }
    if(vehicle->flag == TRAIN) {
        fprintf(file, "Train %d %lf", vehicle->speed, vehicle->way_length);
        train* ptr = &vehicle->t;
        RawOutput(ptr, file);
    }
    if(vehicle->flag == SHIP) {
        fprintf(file, "Ship %d %lf", vehicle->speed, vehicle->way_length);
        ship* ptr = &vehicle->s;
        RawOutput(ptr, file);
    }
    fprintf(file, "\n");
}

/*
 * Вывод данных о транспортном средстве в файл.
 * Работает по тому же принципу, что и случайный ввод.
 * Сначала общие данные, затем особенные.
 */
void Output(vehicle* vehicle, FILE* file) {
    if(vehicle->flag == PLANE) {
        fprintf(file, "%s\n", "Plane");
        fprintf(file, "Speed: %d\nWay length: %lf\nIdeal time of arrival: %lf\n",
                    vehicle->speed, vehicle->way_length, vehicle->ideal_time);
        plane* ptr = &vehicle->p;
        Output(ptr, file);
    }
    if(vehicle->flag == TRAIN) {
        fprintf(file, "%s\n", "Train");
        fprintf(file, "Speed: %d\nWay length: %lf\nIdeal time of arrival: %lf\n",
                    vehicle->speed, vehicle->way_length, vehicle->ideal_time);
        train* ptr = &vehicle->t;
        Output(ptr, file);
    }
    if(vehicle->flag == SHIP) {
        fprintf(file, "%s\n", "Ship");
        fprintf(file, "Speed: %d\nWay length: %lf\nIdeal time of arrival: %lf\n",
                    vehicle->speed, vehicle->way_length, vehicle->ideal_time);
        ship* ptr = &vehicle->s;
        Output(ptr, file);
    }
    fprintf(file, "\n");
    return;
}