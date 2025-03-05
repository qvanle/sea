cmake_minimum_required(VERSION 3.28)
project(Sea)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set source 
set(SRC_HELLO_WORLD src/testing/hello_world.cpp)
set(SRC_GLAD src/glad.c)

# set include  
set(INCLUDE_DIR src/include)

# announcement 
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include GLFW
find_package(glfw3 REQUIRED)

# Add executable
if (CMAKE_BUILD_TYPE STREQUAL "hello_world")
    add_executable(${PROJECT_NAME} ${SRC_HELLO_WORLD} ${SRC_GLAD})
else()
    add_executable(${PROJECT_NAME} ${SRC_HELLO_WORLD} ${SRC_GLAD})
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# Link OpenGL and GLFW
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)
