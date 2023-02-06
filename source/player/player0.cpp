#include "player0.h"

#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/nature.h"


void Player0::NextTurn(SceneInfo &scene) {
    Player::NextTurn(scene);
    scene.sudden_death_info.decrease_turns_left();

    int turns_after_sudden_death = -scene.sudden_death_info.get_turns_left();
    if (turns_after_sudden_death < 0) {
        return;
    }
    auto rows_count = static_cast<int>(scene.grid.get_rows_count());
    auto columns_count = static_cast<int>(scene.grid.get_columns_count());

    int rows_minimum = turns_after_sudden_death;
    int rows_maximum = rows_count - turns_after_sudden_death - 1;

    int columns_minimum = turns_after_sudden_death;
    int columns_maximum = columns_count - turns_after_sudden_death - 1;

    for (int i = rows_minimum; i <= rows_maximum; ++i) {
        DeleteOtherAndSpawnSea({i, columns_minimum}, scene.grid);
        DeleteOtherAndSpawnSea({i, columns_maximum}, scene.grid);
    }

    for (int j = columns_minimum; j <= columns_maximum; ++j) {
        DeleteOtherAndSpawnSea({rows_minimum, j}, scene.grid);
        DeleteOtherAndSpawnSea({rows_maximum, j}, scene.grid);
    }
}

void Player0::DeleteOtherAndSpawnSea(std::pair<int, int> coord, Grid &grid) {
    if (grid.is_coord_out_of_range(coord)) {
        return;
    }
    auto cell = grid.get_cell(coord);
    if (!cell->get_building()->is_empty()) {
        cell->get_building()->Kill(grid);
        grid.DeleteBuilding(coord);
    }

    if (grid.get_cell(coord)->is_suburb()) {
        grid.DeleteSuburb(coord);
    }

    if (!cell->get_unit()->is_empty()) {
        grid.DeleteUnit(coord);
    }

    grid.SetPlayer(coord, kPlayerIndex);

    grid.CreateBuilding<NaturalBuilding>(coord, "sea");
}
