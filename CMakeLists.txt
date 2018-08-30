cmake_minimum_required(VERSION 3.12)
project(RayTracer)

message("Using CMAKE version : ${CMAKE_VERSION}")
message("Using C++ compiler: '${CMAKE_CXX_COMPILER}'")

message("From top level : ")
message("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)

# is this necessary? -- YES, otherwise the libs wont be found!
add_subdirectory(core)
add_subdirectory(Materials)
add_subdirectory(Shapes)

# Add SDL2
find_package(SDL2 REQUIRED)
message("${SDL2_INCLUDE_DIR} added to include directories")
include_directories(${SDL2_INCLUDE_DIRS})

# need to include the main project dir
include_directories(${CMAKE_SOURCE_DIR})

add_executable(ray_tracer main.cpp)

target_link_libraries(ray_tracer PRIVATE ${SDL2_LIBRARIES} core materials shapes)