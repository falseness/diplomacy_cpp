cmake_minimum_required(VERSION 3.13)

project(Diplomacy)

set(CMAKE_CXX_STANDARD 20)
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
        source/drawable_objects_groups/game_scene/grid/grid.cpp
        source/drawable_objects/cell/hexagon.cpp
        source/options/game.cpp source/drawable_objects/cell/cell.cpp
        source/drawable_objects/cell/coord_converter.cpp
        source/sfml_facades/library_facade.cpp
        source/utility/color.cpp
        source/options/hexagon.cpp
        source/player/player.cpp
        source/player/entity_stats.cpp
        source/drawable_objects/entity.cpp
        source/sfml_facades/assets_manager.cpp
        source/utility/vector2d.cpp
        source/utility/segment.cpp
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
        source/drawable_objects/building/barrack.cpp
        source/drawable_objects_groups/interfaces/production_slots.cpp
        source/drawable_objects_groups/interfaces/unit_production.cpp
        source/player/players.cpp
        source/next_turn/next_turn_button.cpp
        source/drawable_objects/interface_elements/triangle.cpp
        source/player/factories/entity.cpp
        source/player/factories/building_and_suburb.cpp
        source/drawable_objects/interface_elements/rounded_rectangle_with_text.cpp
        source/drawable_objects_groups/interfaces/town_production.cpp
        source/drawable_objects/interface_elements/switch_button.cpp
        source/drawable_objects/hittable_entity.cpp
        source/drawable_objects/selection_border.cpp source/drawable_objects_groups/interfaces/building_production_slots.cpp source/drawable_objects_groups/interfaces/building_production_slots.h source/drawable_objects_groups/game_scene/undo_button.cpp source/drawable_objects_groups/game_scene/undo_button.h source/drawable_objects_groups/game_scene/grid/cells.cpp source/drawable_objects_groups/game_scene/grid/cells.h source/drawable_objects_groups/game_scene/grid/action.cpp source/drawable_objects_groups/game_scene/grid/action.h source/drawable_objects/unit/range/range_unit.cpp source/drawable_objects/unit/range/range_unit.h source/drawable_objects/unit/range/range_unit_logic.cpp source/drawable_objects/unit/range/range_unit_logic.h source/player/factories/outside_building.h source/player/factories/building.h source/drawable_objects/building/outside_building.cpp source/drawable_objects/building/outside_building.h source/drawable_objects/unit/range/catapult.cpp source/drawable_objects/unit/range/catapult.h source/drawable_objects/unit/range/catapult_logic.cpp source/drawable_objects/unit/range/catapult_logic.h source/player/player0.cpp source/utility/fps_counter.cpp)

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



