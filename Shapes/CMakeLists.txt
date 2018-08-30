cmake_minimum_required(VERSION 3.12)

project(shapes_lib)

message("Processing Shapes")
message("${RayTracer_SOURCE_DIR} added to include directories")
include_directories(${RayTracer_SOURCE_DIR})

add_library(
    shapes
    STATIC
    Hitable.h
    Hitable_list.h
    Hitable_list.cpp
    Sphere.h
    Sphere.cpp
)

target_include_directories(
    shapes
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)