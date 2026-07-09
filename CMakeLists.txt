cmake_minimum_required(VERSION 3.19)
project(utf-8-bom-remover C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(utf-8-bom-remover main.c)