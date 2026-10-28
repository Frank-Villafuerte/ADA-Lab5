cmake_minimum_required(VERSION 3.10)
project(app)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE Core)
