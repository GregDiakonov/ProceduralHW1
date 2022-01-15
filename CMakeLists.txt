cmake_minimum_required(VERSION 3.21)
project(ProceduralHW)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ProceduralHW
        container.cpp
        container.h
        main.cpp
        plane.h
        ship.h
        train.h
        vehicle.cpp
        vehicle.h plane.cpp ship.cpp Train.cpp)
