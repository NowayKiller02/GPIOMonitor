cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GPIOMonitor)

add_executable(GPIOMonitor main.c)

target_link_libraries(GPIOMonitor PJ_RPI)

install(FILES PJ_RPI.h DESTINATION include)
include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)
target_link_libraries(GPIOMonitor mariadb)
