cmake_minimum_required(VERSION 3.26)
project(course C)

set(CMAKE_C_STANDARD 11)

add_executable(course main.c
tasks_lab19/tasks.c)

add_subdirectory(libs)

target_link_libraries(course data_structures)
target_link_libraries(course algorithms)
