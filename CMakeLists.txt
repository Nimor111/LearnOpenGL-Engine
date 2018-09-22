cmake_minimum_required(VERSION 3.7)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/std_image.cpp src/main.cpp libraries/GLAD/src/glad.c)
set(GLOB_RECURSE HEADER_FILES include/*.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

include_directories(include)

#Include library files
include_directories(libraries/GLAD/include)
include_directories(libraries/glm/include)

file(COPY resources DESTINATION ${dir}/build)

#Add deps
add_subdirectory(libraries)

add_executable(LearnOpenGL ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(LearnOpenGL glfw)
