# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.
cmake_minimum_required(VERSION 3.30)
project(Philosophers C)

include(cmake/utils.cmake)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC_DIR philo/src/*.c)

include_directories(philo/include)

add_executable(Philosophers
        ${SRC_DIR}
)

target_compile_options(Philosophers PRIVATE -pthread)
target_link_libraries(Philosophers pthread)