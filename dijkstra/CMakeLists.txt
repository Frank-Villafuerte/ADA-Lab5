cmake_minimum_required(VERSION 3.10)
project(dijkstra)

add_executable(dijkstra main.cpp)

target_link_libraries(dijkstra PRIVATE Core)
