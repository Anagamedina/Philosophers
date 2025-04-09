cmake_minimum_required(VERSION 3.30)

project(Philosophers_ana C)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC_DIR philo/src/*.c)

include_directories(philo/includes)

add_executable(Philosophers
        ${SRC_DIR}
)

target_compile_options(Philosophers PRIVATE -lpthread)
target_link_libraries(Philosophers pthread)