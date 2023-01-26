#include "building_and_suburb.h"
#include "source/drawable_objects/building/town.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "deque"
#include <cassert>


BuildingAndSuburbFactory::BuildingAndSuburbFactory(PlayersEntitiesFactories &all_factories, std::string name) {
    assert(all_factories.buildings_production_stats.count(name));
}

unsigned int BuildingAndSuburbFactory::get_turns_left(const Player& player, const ProductionInfo& production) const {
    return player.get_factories_stats().buildings_production_stats.find(production.name)->
            second.turns - production.turns;
}

void BuildingAndSuburbFactory::Select(SceneInfo& scene, const Town* town) {
    auto suburbs = town->get_suburbs(scene.grid);

    std::vector<std::pair<int, int>> visited_cells;

    scene.grid.logic_helper_.increment_counter();

    Grid& grid = scene.grid;

    for (auto suburb : suburbs) {
        grid.logic_helper_.visit(suburb);
        grid.logic_helper_.set_info(suburb, -1);
    }

    std::deque<std::pair<int, int>> coords;
    coords.push_back(town->get_coord());
    grid.logic_helper_.set_info(coords.front(), 0);

    visited_cells.push_back(coords.front());


    while (!coords.empty()) {
        auto coord = coords.front();
        coords.pop_front();

        int distance = grid.logic_helper_.get_info(coord);
        //assert(grid.get_cell(coord)->is_suburb());
        auto neighbours = grid.get_neighbours(coord);
        for (auto neighbour : neighbours) {
            if (grid.is_coord_out_of_range(neighbour) || !grid.get_cell(neighbour)->is_my_turn())
                continue;
            if (grid.logic_helper_.is_visited(neighbour) && grid.logic_helper_.get_info(neighbour) != -1)
                continue;
            BFSBody(visited_cells, grid, coords, distance, neighbour);
        }
    }

    scene.grid.logic_helper_.increment_counter();

    for (auto suburb : visited_cells) {
        grid.logic_helper_.visit(suburb);
    }
    scene.selection_border.UpdateBorder(visited_cells, scene.grid.logic_helper_);
}

void SuburbFactory::BFSBody(std::vector<std::pair<int, int>>& visited_cells, Grid& grid,
                              std::deque<std::pair<int, int>>& coords, int distance,
                              const std::pair<int, int>& neighbour) const {
    bool is_suburb = grid.logic_helper_.is_visited(neighbour);
    grid.logic_helper_.visit(neighbour);
    visited_cells.push_back(neighbour);
    grid.logic_helper_.set_info(neighbour, distance + 1);
    if (is_suburb)
        coords.push_back(neighbour);
}

SuburbFactory::SuburbFactory(PlayersEntitiesFactories &all_factories, std::string name) :
        BuildingAndSuburbFactory(all_factories, std::move(name)){}


ClickResponse SuburbFactory::HandleClick(SceneInfo &scene, const Vector2D &click_pos,
                                         const GameOptions &game_options, const Town* town) const {
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    if (!is_correct_click(scene, coord) || scene.grid.get_cell(coord)->is_suburb())
        return {true, false, false};

    int distance = scene.grid.logic_helper_.get_info(coord);
    int cost = kArithmeticProgressionDelta * (distance - 1) + kBaseCost;
    assert(!scene.grid.get_cell(coord)->is_suburb());

    scene.grid.AddSuburb(town->get_coord(), coord);
    scene.town_production_interface.ReClick(scene);

    return {false, false, false};
}

bool BuildingAndSuburbFactory::is_correct_click(SceneInfo &scene, std::pair<int, int> coord) {
    Grid& grid = scene.grid;
    return !grid.is_coord_out_of_range(coord) && grid.logic_helper_.is_visited(coord) &&
        grid.logic_helper_.get_info(coord) != -1;
}


