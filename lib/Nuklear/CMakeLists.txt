cmake_minimum_required(VERSION 3.17)
project(nuklear)

set(CMAKE_C_STANDARD 99)

add_library(nuklear nuklear.c nuklear.h nuklear_glfw_gl4.h)
