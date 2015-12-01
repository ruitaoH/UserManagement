cmake_minimum_required(VERSION 3.3)
project(task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(m)

set(SOURCE_FILES main.c first.c first.h second.c second.h third.c third.h forth.c forth.h)
add_executable(task3 ${SOURCE_FILES} ./cJSON/cJSON.h ./cJSON/cJSON.c)