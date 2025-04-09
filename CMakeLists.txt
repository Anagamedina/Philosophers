cmake_minimum_required(VERSION 3.30)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC philo/src/*.c)

include_directories(philo/include)

add_executable(philosophers
        philo/src/main.c
        philo/src/death_monitor.c
        philo/src/fork_control.c
        philo/src/parse_args.c
        philo/src/parse_utils.c
        philo/src/philosopher_threads.c
)

target_link_libraries(philosophers pthread)