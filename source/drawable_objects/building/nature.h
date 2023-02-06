#include "source/drawable_objects/building/building.h"


class NaturalBuilding : public Building {
public:
    NaturalBuilding(Cell* cell, std::string image_name) : Building(cell, image_name),
                                                          Entity(cell, std::move(image_name)) {}
    [[nodiscard]] inline bool is_passable(size_t asking_player_index) const override {
        return false;
    }
    [[nodiscard]] inline bool can_be_shot(size_t) const override {
        return false;
    }
};


class Mountain : public NaturalBuilding {
public:
    Mountain(Cell* cell, std::string image_name) : NaturalBuilding(cell, image_name),
        Entity(cell, std::move(image_name)) {}
    [[nodiscard]] inline bool can_be_shot_through() const override {
        return false;
    }
};
