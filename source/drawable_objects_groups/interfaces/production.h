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
    Image gold_image_;
    RightAlignedText gold_text_;

    class ProductionSlots : public DrawableObjectsGroup {
        Vector2D interval_between_;
        Image production_image_;
        Text cost_text_;
        RoundedRectangleWithText button_;
        Barrack* barrack_ = nullptr;
        void add_to_pos(const Vector2D&);
    public:
        static const std::string kCostTextStart;
        void update(Barrack*);
        ProductionSlots(Vector2D pos, float background_width, float background_height, const Screen&);
        void Draw(Screen& screen, const GameOptions&) override;
    };

    std::unique_ptr<ProductionInterface::ProductionSlots> production_slots_;
public:
    static const float kHeightWidthBestRatio;
    explicit ProductionInterface(const Screen& screen);
    void update(Barrack*);
    void Draw(Screen& screen, const GameOptions&) override;

};
