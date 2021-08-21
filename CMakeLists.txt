cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

add_executable(Learn "src/LearnOpenGL.cpp")

add_subdirectory(glad/)

target_link_libraries(Learn glfw3 dl GL X11 pthread glad)