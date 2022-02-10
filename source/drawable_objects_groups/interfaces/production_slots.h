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

class ProductionSlots : public DrawableObjectsGroup, public ClickableObject {
protected:
    Vector2D interval_between_;
private:
    Image production_image_;
    Text cost_text_;
protected:
    RoundedRectangleWithText button_;
private:
    Barrack* barrack_ = nullptr;
    void add_to_pos(const Vector2D&);

protected:
    [[nodiscard]] virtual bool should_display_button(const std::pair<std::string, EntityProductionStats>&) const;
    virtual void set_button_text(const std::pair<std::string, EntityProductionStats>&);

    template <typename T>
    auto get_corresponding_stat(const Vector2D& pos, const std::map<std::string, T>& stats) {
        int i = 0;
        for (auto stat = stats.begin(); stat != stats.end(); ++stat, ++i) {
            if (button_.is_inside(pos)) {
                add_to_pos(interval_between_ * static_cast<float>(-i));
                return stat;
            }
            add_to_pos(interval_between_);
        }
        add_to_pos(interval_between_ * static_cast<float>(-i));
        return stats.end();
    }
    virtual void DrawButtonsByStats(Screen &screen, const GameOptions& game_options,
                                    const std::map<std::string, EntityProductionStats>& stats);
    virtual bool CheckButtonsClick(const Vector2D& pos, SceneInfo& scene,
                                   const PlayersEntitiesFactories& factories);
public:
    [[nodiscard]] virtual float get_bottom() const;
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
    [[nodiscard]] virtual bool can_start_new_production() const;
};
