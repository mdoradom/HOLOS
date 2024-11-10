cmake_minimum_required(VERSION 3.10)
project(ProcessTest2Shared)

# Add the executables
add_executable(shared_inc shared_inc.cpp)
add_executable(shared_inc_safe shared_inc_safe.cpp)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(shared_inc ${SDL2_LIBRARIES})
target_link_libraries(shared_inc_safe ${SDL2_LIBRARIES})