cmake_minimum_required(VERSION 3.15)
project(EATEXPRESS)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)

include_directories(.)

add_executable(EATEXPRESS
        Client.cpp
        Client.h
        GraphViewer/connection.cpp
        GraphViewer/connection.h
        Deliverer.cpp
        Deliverer.h
        Delivery.cpp
        Delivery.h
        GraphViewer/edgetype.h
        Graph.h
        GraphViewer/graphviewer.cpp
        GraphViewer/graphviewer.h
        main.cpp
        MutablePriorityQueue.h
        parse.cpp
        parse.h
        Point.cpp
        Point.h
        Restaurant.cpp
        Restaurant.h
        Utils.cpp
        Utils.h
        Vehicle.cpp
        Vehicle.h Parse.h Parse.cpp Company.cpp Company.h)
