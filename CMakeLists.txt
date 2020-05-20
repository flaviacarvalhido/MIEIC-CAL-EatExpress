cmake_minimum_required(VERSION 3.15)
project(Projeto_Cal)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto_Cal
        Client.cpp
        Client.h
        Deliverer.cpp
        Deliverer.h
        Delivery.cpp
        Delivery.h
        Graph.h
        main.cpp
        parse.cpp
        parse.h
        Point.cpp
        Point.h
        Restaurant.cpp
        Restaurant.h
        Utils.cpp
        Utils.h
        Vehicle.cpp
        Vehicle.h)
