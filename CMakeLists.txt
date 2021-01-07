cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

set(project_name Battle_City)

project(Battle_City)

add_executable(Battle_City  Source/main.cpp Source/Renderer/ShaderProgram.cpp Source/Renderer/ShaderProgram.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

target_link_libraries(Battle_City glfw)

add_subdirectory(external/glad)

target_link_libraries(Battle_City GLAD)