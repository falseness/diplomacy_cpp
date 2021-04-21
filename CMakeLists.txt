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
        source/drawable_objects_groups/drawable_objects_group.cpp
        source/drawable_objects_groups/scene.cpp
        source/drawable_objects_groups/game_scene/game_scene.cpp
        source/drawable_objects_groups/game_scene/grid.cpp
        source/drawable_objects/cell/hexagon.cpp
        source/options/options.cpp source/drawable_objects/cell/cell.cpp
        source/drawable_objects/cell/coord_translation.cpp
        source/sfml_facades/library_facade.cpp
        source/utility/color.cpp
        source/options/hexagon.cpp
        source/sfml_facades/utility/sfml_color.cpp)

add_executable(Diplomacy ${MAIN_SOURCE})
#---
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Diplomacy sfml-graphics sfml-audio)
#---



