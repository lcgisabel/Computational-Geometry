cmake_minimum_required(VERSION 2.6)

add_executable(tetgen tetgen.cxx predicates.cxx)

add_library(tet STATIC tetgen.cxx predicates.cxx)

set_target_properties(tet PROPERTIES "COMPILE_DEFINITIONS" TETLIBRARY)