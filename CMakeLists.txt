cmake_minimum_required(VERSION 3.15)
project(EATEXPRESS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EATEXPRESS
        Client.cpp
        Client.h
        Deliverer.cpp
        Deliverer.h
        Delivery.cpp
        Delivery.h
        Graph.h
        main.cpp
        Restaurant.cpp
        Restaurant.h
        Utils.cpp
        Utils.h
        Vehicle.cpp
        Vehicle.h Parse.h Parse.cpp)
