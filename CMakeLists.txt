cmake_minimum_required(VERSION 3.1)

project(Diplomacy)

#---
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#---

include_directories(${PROJECT_SOURCE_DIR})
set(    MAIN_SOURCE
        main/main.cpp
        source/game.cpp
        source/sfml_facades/event_manager.cpp
        source/sfml_facades/screen.cpp
        source/sprites_groups/sprites_group.cpp
        source/sprites_groups/scene.cpp
        source/sprites_groups/game_scene/game_scene.cpp
        source/sprites_groups/game_scene/grid.cpp
        source/sprites/cell/hexagon.cpp
        source/options/options.cpp source/sprites/cell/cell.cpp source/sprites/cell/cell.h source/sprites/cell/coord_translation.cpp source/sprites/cell/coord_translation.h source/geometry/point.h)

add_executable(Diplomacy ${MAIN_SOURCE})
#---
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Diplomacy sfml-graphics sfml-audio)
#---



