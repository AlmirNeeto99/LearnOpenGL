cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(run ${SRCS})

add_subdirectory(glad/)

target_link_libraries(run glfw3 dl GL X11 pthread glad)