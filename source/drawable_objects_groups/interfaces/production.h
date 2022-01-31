#include <source/sfml_facades/screen.h>
#include <source/utility/vector2d.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/image.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle_with_text.h>
#include <nlohmann/json.hpp>

#pragma once

class Barrack;
class PlayersEntitiesFactories;

class ProductionInterface: public DrawableObjectsGroup {
    RoundedRectangle background_;
    Barrack* barrack_ = nullptr;
    const PlayersEntitiesFactories* factories_ = nullptr;
    RoundedRectangleWithText button_;
public:
    explicit ProductionInterface(const Screen& screen);
    void Draw(Screen& screen, const GameOptions&) override;
    void update(Barrack*);

};
