cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

file(GLOB SRCS "src/*.cpp")

add_executable(Learn ${SRCS})

add_subdirectory(glad/)

target_link_libraries(Learn glfw3 dl GL X11 pthread glad)