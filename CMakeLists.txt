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
        source/sfml_facades/assets_manager.cpp
        source/utility/vector2d.cpp
        source/utility/object_size.cpp
        source/drawable_objects/unit/unit.cpp
        source/utility/geometry.cpp
        source/drawable_objects/unit/unit_logic.cpp
        source/drawable_objects_groups/game_scene/grid_logic_helper.cpp
        source/drawable_objects_groups/interfaces/entity_info.cpp
        source/drawable_objects/interface_elements/rounded_rectangle.cpp
        source/drawable_objects/interface_elements/text.cpp
        source/drawable_objects/interface_elements/image.cpp
        source/drawable_objects/building/building.cpp
        source/drawable_objects/building/building_with_hp.cpp
        source/drawable_objects/building/town.cpp
        source/drawable_objects/building/suburb_building.cpp
        source/drawable_objects/building/barrack.cpp source/drawable_objects/building/barrack.h source/drawable_objects_groups/interfaces/production.cpp source/drawable_objects_groups/interfaces/production.h source/player/players.cpp source/player/players.h source/next_turn/next_turn_button.cpp source/next_turn/next_turn_button.h source/drawable_objects/interface_elements/triangle.cpp source/drawable_objects/interface_elements/triangle.h)

add_executable(Diplomacy ${MAIN_SOURCE})
#---
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_SOURCE_DIR}/bin
        )
add_dependencies(Diplomacy copy_assets)


target_link_libraries(Diplomacy PRIVATE sfml-graphics sfml-audio nlohmann_json::nlohmann_json)
#---



