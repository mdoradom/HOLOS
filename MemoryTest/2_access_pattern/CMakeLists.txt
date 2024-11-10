cmake_minimum_required(VERSION 3.10)
project(MemoryTest2AccessPattern)

# Add the executable
add_executable(mm-ijk mm-ijk.c measure.c sampler.c)
add_executable(mm-ijk2 mm-ijk2.c measure.c sampler.c)
add_executable(mm-jki mm-jki.c measure.c sampler.c)
add_executable(mm-kij mm-kij.c measure.c sampler.c)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(mm-ijk ${SDL2_LIBRARIES})
target_link_libraries(mm-ijk2 ${SDL2_LIBRARIES})
target_link_libraries(mm-jki ${SDL2_LIBRARIES})
target_link_libraries(mm-kij ${SDL2_LIBRARIES})