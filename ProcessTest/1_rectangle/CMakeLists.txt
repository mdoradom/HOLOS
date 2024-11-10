cmake_minimum_required(VERSION 3.10)
project(ProcessTest1Rectangle)

# Add the executables
add_executable(ParallelRectangle ParallelRectangle.cpp)
add_executable(SingleRectangle SingleRectangle.cpp)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(ParallelRectangle ${SDL2_LIBRARIES})
target_link_libraries(SingleRectangle ${SDL2_LIBRARIES})