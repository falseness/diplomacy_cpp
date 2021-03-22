cmake_minimum_required(VERSION 3.1)

project(Diplomacy)

#---
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#---

include_directories(${PROJECT_SOURCE_DIR})
set(MAIN_SOURCE main/main.cpp)
add_executable(Diplomacy ${MAIN_SOURCE})

#---
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Diplomacy sfml-graphics sfml-audio)
#---
add_subdirectory(${PROJECT_SOURCE_DIR}/source)
target_link_libraries(SubdirectoryProject)
