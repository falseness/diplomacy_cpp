cmake_minimum_required(VERSION 3.1)
project(SubdirectoryProject)

set(SOURCE_LIB game.cpp)
add_library(SubdirectoryProject SHARED ${SOURCE_LIB})
