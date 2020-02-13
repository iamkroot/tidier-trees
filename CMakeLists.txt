cmake_minimum_required(VERSION 3.16)
project(tidier_trees)
set(OpenGlLinkers -lGL -lglfw -lGLEW)
set(CMAKE_CXX_STANDARD 20)

add_executable(tidier_trees main.cpp GLUtils.cpp GLUtils.h Vertex2D.cpp Vertex2D.h Line.cpp Line.h Drawable.h)
target_link_libraries(tidier_trees ${OpenGlLinkers})
