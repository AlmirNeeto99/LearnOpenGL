cmake_minimum_required(VERSION 3.16)

project(Learn)

file(GLOB UTILS "*.cpp")

add_library(Utils ${UTILS})