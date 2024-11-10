cmake_minimum_required(VERSION 3.10)
project(HOLOS)

# Añadir subdirectorios
add_subdirectory(MemoryTest/1_matrix)
add_subdirectory(MemoryTest/2_access_pattern)
add_subdirectory(MemoryTest/3_dynamic_memory)
add_subdirectory(ProcessTest/1_rectangle)
add_subdirectory(ProcessTest/2_shared)
add_subdirectory(FileTest)
