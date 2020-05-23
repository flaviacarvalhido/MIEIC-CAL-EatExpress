cmake_minimum_required(VERSION 3.15)
project(EATEXPRESS)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)

include_directories(.)
include_directories(GraphViewer)

add_executable(EATEXPRESS
        GraphViewer/connection.cpp
        GraphViewer/connection.h
        GraphViewer/edgetype.h
        GraphViewer/graphviewer.cpp
        GraphViewer/graphviewer.h
        Client.cpp
        Client.h
        Company.cpp
        Company.h
        Deliverer.cpp
        Deliverer.h
        Delivery.cpp
        Delivery.h
        Graph.h
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
        Vehicle.h)
