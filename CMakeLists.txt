cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

set(project_name Battle_City)

project(${project_name})

add_executable(${project_name}  Source/main.cpp Source/Renderer/ShaderProgram.cpp Source/Renderer/ShaderProgram.h Source/Resources/ResourceManager.cpp Source/Resources/ResourceManager.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

target_link_libraries(${project_name} glfw)

add_subdirectory(external/glad)

target_link_libraries(${project_name} GLAD)

set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${project_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:${project_name}>/Resources/)