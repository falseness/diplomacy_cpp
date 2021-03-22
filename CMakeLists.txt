cmake_minimum_required(VERSION 3.6)

add_compile_options(-lcairo)

project(MainProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 11)

set(MAIN_SOURCE main.cpp)
add_executable(MainProject ${MAIN_SOURCE})

#---
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#---

find_package(Cairo)
include_directories(${Cairo_INCLUDE_DIRS})
target_link_libraries(MainProject ${Cairo_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR})

#---


