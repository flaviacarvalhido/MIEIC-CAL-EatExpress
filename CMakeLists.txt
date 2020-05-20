cmake_minimum_required(VERSION 3.15)
project(EATEXPRESS)

set(CMAKE_CXX_STANDARD 14)

add_executable(EATEXPRESS main.cpp Client.cpp Client.h Restaurant.cpp Restaurant.h Deliverer.cpp Deliverer.h Vehicle.cpp Vehicle.h Delivery.cpp Delivery.h Utils.h Utils.cpp)