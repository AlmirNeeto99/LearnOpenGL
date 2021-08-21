cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

add_executable(FirstExample "src/Main.cpp")

add_subdirectory(glad/)

target_link_libraries(FirstExample glfw3 dl GL X11 pthread glad)