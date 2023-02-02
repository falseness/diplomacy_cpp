#include "player0.h"

#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/building/nature.h"


void Player0::NextTurn(SceneInfo &scene) {
    Player::NextTurn(scene);

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
        //scene.grid.get_cell(i, );
    }
    //if (rows_minimum <= rows_maximum)
}

void Player0::SpawnSea(std::pair<int, int> coord, Grid &grid) {
    auto cell = grid.get_cell(coord);
    if (!cell->get_building()->is_empty()) {
        grid.DeleteBuilding(coord);
    }
    if (cell->is_suburb()) {
        grid.DeleteSuburb(coord);
    }
    if (!cell->get_unit()->is_empty()) {
        grid.DeleteUnit(coord);
    }

    grid.SetPlayer(coord, kPlayerIndex);

    //grid.CreateBuilding<NaturalBuilding>()
}
