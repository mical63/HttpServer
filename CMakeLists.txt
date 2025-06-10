cmake_minimum_required(VERSION 3.0.0)
project(HttpServer-c)
set(HOME /home/mical/HttpSevver/HttpServer-C)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/build)
set(CMAKE_CXX_STANDARD 11)
include_directories(${HOME}/include)

aux_source_directory(${HOME}/src SRC)
# file(GLOB SRC ${PROJECT_SOURCE_DIR}/src)

add_executable(a.out ${SRC})
