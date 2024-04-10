cmake_minimum_required(VERSION 3.27)
project(GraphLibrary)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphLibrary main.cpp
        StringOp.h
        Book.h
        Nodebook.h
        Graph.h
        Vertex.h)
