cmake_minimum_required(VERSION 3.12)

project(materials_lib)

message("Processing materials")
message("${RayTracer_SOURCE_DIR} added to include directories")
include_directories(${RayTracer_SOURCE_DIR})

add_library(
    materials
    STATIC
    Material.h
    Metal.h
    Metal.cpp
    Lambertian.h
    Lambertian.cpp
    Dialectric.h
    Dialectric.cpp
)

target_include_directories(
    materials
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)