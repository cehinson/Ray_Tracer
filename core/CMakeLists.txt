cmake_minimum_required(VERSION 3.12)

project(core_lib)

message("Processing core")
message("${RayTracer_SOURCE_DIR} added to include directories")
include_directories(${RayTracer_SOURCE_DIR})

add_library(
    core
    STATIC
    Vec3.h
    MyRandom.h
    MyRandom.cpp
    MyMathConstants.h
    Ray.h
    Camera.h
)

# is this necessary?
target_include_directories(
    core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)