cmake_minimum_required(VERSION 3.12)
project(Ray_Tracer_Test)
message("in tests")

message("${RayTracer_SOURCE_DIR} added to include directories")
include_directories(${RayTracer_SOURCE_DIR})

# Add Catch2
find_package(Catch2 REQUIRED)

# Dunno if this is necessary
add_executable (rt_tests Ray_Tracer_Tests.cpp Vec3_Tests.cpp Camera_Tests.cpp)

target_link_libraries(
    rt_tests 
    PRIVATE
    Catch2::Catch2
    core
    materials
    shapes
)

include(CTest)
include(Catch)
catch_discover_tests(rt_tests)