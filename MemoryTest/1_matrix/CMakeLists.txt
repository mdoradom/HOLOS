cmake_minimum_required(VERSION 3.10)
project(MemoryTest1Matrix)

# Add the executable
add_executable(matriu matriu.c measure.c sampler.c)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(matriu ${SDL2_LIBRARIES})