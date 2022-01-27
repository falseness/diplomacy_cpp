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
        source/drawable_objects/cell/coord_converter.cpp
        source/sfml_facades/library_facade.cpp
        source/utility/color.cpp
        source/options/hexagon.cpp
        source/sfml_facades/utility/sfml_color.cpp
        source/player/player.cpp
        source/player/entity_stats.cpp
        source/drawable_objects/entity.cpp
        source/sfml_facades/image_manager.cpp
        source/utility/vector2d.cpp
        source/utility/object_size.cpp
        source/drawable_objects/unit/unit.cpp
        source/utility/geometry.cpp source/drawable_objects/unit/unit_logic.cpp source/drawable_objects/unit/unit_logic.h source/drawable_objects_groups/game_scene/grid_logic_helper.cpp source/drawable_objects_groups/game_scene/grid_logic_helper.h)

add_executable(Diplomacy ${MAIN_SOURCE})
#---
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_SOURCE_DIR}/bin
        )
add_dependencies(Diplomacy copy_assets)


target_link_libraries(Diplomacy sfml-graphics sfml-audio)
#---



