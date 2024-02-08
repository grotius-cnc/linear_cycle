cmake_minimum_required(VERSION 3.5)

project(linear_cycle LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    linear_cycle.h
    linear_cycle.cpp
)

add_executable(runtest ${PROJECT_SOURCES} )


