cmake_minimum_required(VERSION 3.10)
project(bellmanford)

add_executable(bellmanford main.cpp)

target_link_libraries(bellmanford PRIVATE Core)
