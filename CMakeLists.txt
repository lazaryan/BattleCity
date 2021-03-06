﻿cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

# Add project files (personaly)
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    "src/Renderer/ShaderPropgram.cpp"
    "src/Renderer/ShaderPropgram.hpp"
    "src/Resources/stb_image.h"
    "src/Resources/ResourceManager.cpp"
    "src/Resources/ResourceManager.hpp"
    "src/Renderer/Texture2D.cpp"
    "src/Renderer/Texture2D.hpp"
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set options for glfw cmake build
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add Glfw lib in my project
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Add Glad lib in my project
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
