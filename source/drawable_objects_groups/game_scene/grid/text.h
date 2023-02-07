#pragma once

#include "source/drawable_objects/interface_elements/text.h"


class Grid;

class GridText : public DrawableObject {
protected:
    const Grid& grid_;
    Text text_template_;
protected:
    [[nodiscard]] virtual std::string get_text(std::pair<int, int> coord) const = 0;
    inline virtual void DrawText(std::pair<int, int> coord, Screen& screen, const GameOptions& game_options) {
        set_text_position(coord, screen, game_options);
        text_template_.Draw(screen, game_options);
    }
    void set_text_position(std::pair<int, int> coord, Screen& screen, const GameOptions& game_options);
public:
    explicit GridText(const Grid& grid);
    void Draw(Screen& screen, const GameOptions& game_options) override;
};

class GridRegularCellInfo : public GridText {
    [[nodiscard]] std::string get_text(std::pair<int, int> coord) const override;
    void DrawText(std::pair<int, int> coord, Screen& screen, const GameOptions& game_options) override;
public:
    using GridText::GridText;
};

/*
class GridSelectionText : public GridText {
public:
    explicit GridSelectionText(const Grid& grid_cells);
    void Draw(Screen& screen, const GameOptions& game_options) override;
};
*/