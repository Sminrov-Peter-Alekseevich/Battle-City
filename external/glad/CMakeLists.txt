CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

project(GLAD)

add_library(GLAD STATIC include/glad/glad.h src/glad.c)

target_include_directories(GLAD PUBLIC include/)