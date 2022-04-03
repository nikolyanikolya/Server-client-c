cmake_minimum_required(VERSION 3.17)
project(VK_project C)

set(CMAKE_C_STANDARD 11)
include_directories(include)
add_executable(client src/client.c src/errproc.c)
add_executable(server src/server.c src/errproc.c)