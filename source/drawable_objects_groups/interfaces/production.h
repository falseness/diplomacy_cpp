#include <source/sfml_facades/screen.h>
#include <source/utility/vector2d.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>
#include <source/drawable_objects/interface_elements/image.h>
#include <source/drawable_objects_groups/drawable_objects_group.h>
#include <source/drawable_objects/clickable_object.h>
#include <source/drawable_objects/interface_elements/rounded_rectangle_with_text.h>
#include <source/player/player.h>
#include <nlohmann/json.hpp>

#pragma once

class Barrack;
class PlayersEntitiesFactories;

class ProductionInterface: public DrawableObjectsGroup, public ClickableObject {
    RoundedRectangle background_;
    Barrack* barrack_ = nullptr;
    RightAlignedText gold_text_;
protected:
    Image gold_image_;
    [[nodiscard]] float get_center_x() const;
    [[nodiscard]] float get_width() const;
    class ProductionSlots : public DrawableObjectsGroup, public ClickableObject {
        Vector2D interval_between_;
        Image production_image_;
        Text cost_text_;
        RoundedRectangleWithText button_;
        Barrack* barrack_ = nullptr;
        void add_to_pos(const Vector2D&);
        void set_button_text(const std::pair<std::string, UnitProductionStats>&);
        [[nodiscard]] bool is_should_display_button(const std::pair<std::string, UnitProductionStats>&) const;
    public:
        static const Color kButtonBackgroundColor;
        static const Color kButtonTextColor;
        static float get_button_corner_radius(const Screen&);
        static float get_button_border_width(const Screen&);
        static size_t get_button_text_size(const Screen&);

        static const std::string kCostTextStart;
        void update(Barrack*);
        ProductionSlots(Vector2D pos, float background_width, float background_height, const Screen&);
        bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
        void Draw(Screen& screen, const GameOptions&) override;
    };
    static float get_margin_between_gold_image_and_slots(const Screen&);
private:
    std::unique_ptr<ProductionInterface::ProductionSlots> production_slots_;

public:
    static const float kHeightWidthBestRatio;
    explicit ProductionInterface(const Screen& screen);
    void update(Barrack*);
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
    void Draw(Screen& screen, const GameOptions&) override;

};