cmake_minimum_required(VERSION 2.8.9)

file(GLOB SOURCES "./*.cpp")
include_directories("./")
project (Powercrust)
add_executable(powercrust "./code/Powercrust_exe.cpp")




