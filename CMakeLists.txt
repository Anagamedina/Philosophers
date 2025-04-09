cmake_minimum_required(VERSION 3.30)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC philo/src/*.c)

include_directories(philo/include/philo.h)

add_executable(philosophers
    ${SRC}
)
target_compile_options(philosophers PRIVATE -lpthread)
target_link_libraries(philosophers pthread)