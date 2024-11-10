cmake_minimum_required(VERSION 3.10)
project(FileTest)

# Add the executables
add_executable(read_ints read_ints.c)
add_executable(hall_of_fame hall_of_fame.cpp)
add_executable(write_ints write_ints.c)
add_executable(write_string write_string.cpp)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(read_ints ${SDL2_LIBRARIES})
target_link_libraries(hall_of_fame ${SDL2_LIBRARIES})
target_link_libraries(write_ints ${SDL2_LIBRARIES})
target_link_libraries(write_string ${SDL2_LIBRARIES})