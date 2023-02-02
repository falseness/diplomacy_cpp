#include "source/drawable_objects/interface_elements/text.h"


class SuddenDeathInfo : public DrawableObject {
    RightAlignedText text_;
    int turns_to_sudden_death_;
public:
    SuddenDeathInfo(Vector2D position, size_t size, Color color, int turns_to_sudden_death = 30) :
        text_(position, "error", size, color), turns_to_sudden_death_(turns_to_sudden_death) {
        text_.text = std::to_string(turns_to_sudden_death_);
    }
    inline void decrease_turns_left() {
        --turns_to_sudden_death_;
        text_.text = std::to_string(turns_to_sudden_death_);
    }
    [[nodiscard]] inline int get_turns_left() const {
        return turns_to_sudden_death_;
    }
    inline void Draw(Screen& screen, const GameOptions& game_options) override {
        text_.Draw(screen, game_options);
    }
};
