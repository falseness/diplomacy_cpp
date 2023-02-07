#include "text.h"

#include "source/drawable_objects/cell/cell.h"

#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include <iostream>

void GridText::Draw(Screen &screen, const GameOptions &game_options) {
    text_template_.size = game_options.get_text_size();
    for (size_t i = 0; i < grid_.get_rows_count(); ++i) {
        for (size_t j = 0; j < grid_.get_columns_count(); ++j) {
            Vector2D pos = grid_.get_cell({i, j})->get_pos(game_options);
            text_template_.text = get_text({i, j});
            text_template_.set_center(screen.get_real_position_on_grid(pos) + game_options.get_text_offset(), screen);

            DrawText(screen, game_options);
        }
    }
}

GridText::GridText(const Grid &grid) : grid_(grid) {}

std::string GridRegularCellInfo::get_text(std::pair<int, int> coord) const {
    return grid_.get_cell(coord)->get_additional_text_info();
}


/*
GridSelectionText::GridSelectionText(const Grid &grid) : grid_(grid) {
    text_values_.resize(grid.get_rows_count());
    for (auto& u : text_values_) {
        u.resize(grid.get_columns_count());
    }
}

void GridSelectionText::Draw(Screen &screen, const GameOptions &game_options) {
    assert(text_values_.size() == grid_.get_rows_count());
    text_template_.size = game_options.get_text_size();
    for (size_t i = 0; i < text_values_.size(); ++i) {
        assert(text_values_[i].size() == grid_.get_columns_count());
        for (size_t j = 0; j < text_values_[i].size(); ++j) {
            Vector2D pos = grid_.get_cell({i, j})->get_pos(game_options);

            text_template_.set_center(screen.get_real_position_on_grid(pos) + game_options.get_text_offset(), screen);
            text_template_.text = text_values_[i][j];
            text_template_.Draw(screen, game_options);
        }
    }
}

std::string GridSelectionText::get_text(std::pair<int, int>) {
    return std::string();
}


*/
