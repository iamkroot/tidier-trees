cmake_minimum_required(VERSION 3.16)
project(tidier_trees)
set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(tidier_trees main.cpp)
target_link_libraries(tidier_trees ${OpenGlLinkers})
