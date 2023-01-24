#include "source/sfml_facades/screen.h"
#include "source/utility/vector2d.h"
#include "source/drawable_objects/interface_elements/rounded_rectangle.h"
#include "source/drawable_objects/interface_elements/text.h"
#include "source/drawable_objects/interface_elements/image.h"
#include "source/drawable_objects_groups/drawable_objects_group.h"
#include "source/drawable_objects/clickable_object.h"
#include "source/drawable_objects/interface_elements/rounded_rectangle_with_text.h"
#include "source/player/player.h"
#include "source/drawable_objects_groups/interfaces/production_slots.h"
#include <nlohmann/json.hpp>

#pragma once

class Barrack;

class ProductionInterface: public DrawableObjectsGroup, public ClickableObject {
    const Barrack* barrack_ = nullptr;
    RightAlignedText gold_text_;
protected:
    float this_height;
    float this_width;
    [[nodiscard]] Vector2D get_slots_pos(const Screen& screen) const;

    RoundedRectangle background_;
    Image gold_image_;
    [[nodiscard]] float get_center_x() const;
    [[nodiscard]] float get_width() const;
    virtual void UpdateSize();

    static float get_margin_between_gold_image_and_slots(const Screen&);
    std::unique_ptr<ProductionSlots> production_slots_;

public:
    static const float kHeightWidthBestRatio;
    explicit ProductionInterface(const Screen& screen);
    void update(const Barrack*);
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    void Draw(Screen& screen, const GameOptions&) override;
};
