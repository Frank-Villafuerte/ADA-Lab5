cmake_minimum_required(VERSION 3.10)
project(floydwarshall)

add_executable(floydwarshall main.cpp)

target_link_libraries(floydwarshall PRIVATE Core)
