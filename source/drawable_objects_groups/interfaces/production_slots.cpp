#include "production_slots.h"

#include "unit_production.h"
#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects_groups/interfaces/unit_production.h"

bool ProductionSlots::HandleClick(SceneInfo& scene, const Vector2D& pos,
                                                       const GameOptions &game_options) {
    if (!visible_)
        return false;
    assert(barrack_ != nullptr);

    if (!can_start_new_production())
        return false;

    const auto& factories = barrack_->get_player().get_factories_stats();
    return CheckButtonsClick(pos, scene, factories);
}

const std::string ProductionSlots::kCostTextStart = "cost: ";

void ProductionSlots::set_button_text(const std::pair<std::string, EntityProductionStats>& stat) {
    static const std::string kTrainButtonText = "train";
    assert(barrack_ != nullptr);
    if (!barrack_->is_production_in_progress()) {
        button_.text.text = kTrainButtonText;
        return;
    }

    if (should_display_button(stat)) {
        button_.text.text = std::to_string(barrack_->get_turns_left()) + "/" + std::to_string(stat.second.turns);
    }
}

bool ProductionSlots::should_display_button(
        const std::pair<std::string, EntityProductionStats>& stat) const {
    assert(barrack_ != nullptr);
    if (!barrack_->is_production_in_progress())
        return true;
    return stat.first == barrack_->get_training_unit_name();
}

float ProductionSlots::get_button_corner_radius(const Screen& screen) {
    return static_cast<float>(screen.get_height()) * 0.03f;
}

float ProductionSlots::get_button_border_width(const Screen& screen) {
    return static_cast<float>(screen.get_height()) * 0.003f;
}

size_t ProductionSlots::get_button_text_size(const Screen& screen) {
    return static_cast<size_t>(static_cast<float>(screen.get_width()) * 0.04f * 1.15f *
        ProductionInterface::kHeightWidthBestRatio);
}

bool ProductionSlots::CheckButtonsClick(const Vector2D &pos, SceneInfo& scene,
                                                             const PlayersEntitiesFactories& factories) {
    auto stat = get_corresponding_stat(pos, factories.units_production_stats);
    if (stat == factories.units_production_stats.end())
        return false;
    barrack_->StartProduction(ProductionInfo{stat->first, 0});
    barrack_->Select(scene);
    return true;
}

void ProductionSlots::DrawButtonsByStats(
        Screen &screen, const GameOptions& game_options, const std::map<std::string, EntityProductionStats>& stats) {
    int i = 0;
    for (auto stat = stats.begin(); stat != stats.end(); ++stat, ++i) {
        production_image_.name = stat->first;
        production_image_.Draw(screen, game_options);

        cost_text_.text = ProductionSlots::kCostTextStart + std::to_string(stat->second.cost);
        cost_text_.Draw(screen, game_options);

        set_button_text(*stat);
        if (should_display_button(*stat))
            button_.Draw(screen, game_options);
        add_to_pos(interval_between_);
    }
    add_to_pos(interval_between_ * static_cast<float>(-i));
}

float ProductionSlots::get_bottom() const {
    assert(barrack_ != nullptr);
    size_t buttons_count = barrack_->get_player().get_factories_stats().units_production_stats.size();
    return button_.get_bottom() + static_cast<float>(buttons_count) * interval_between_.y;
}

bool ProductionSlots::can_start_new_production() const {
    return !barrack_->is_production_in_progress();
}

ProductionSlots::ProductionSlots(Vector2D pos, float background_width, float background_height,
                                                      const Screen& screen) :
        interval_between_(0, background_height * 0.25f) {
    auto screen_w = static_cast<float>(screen.get_width());
    auto screen_h = static_cast<float>(screen.get_height());
    production_image_.size = {screen_h * 0.1f, screen_h * 0.1f};
    production_image_.position = pos;



    cost_text_.size = static_cast<size_t>(screen_w * 0.04f * 1.15f * ProductionInterface::kHeightWidthBestRatio);
    cost_text_.position = {pos.x + screen_w * 0.22f * 0.26f - cost_text_.get_width(screen) / 2,
                           pos.y - cost_text_.get_height(screen) / 2};


    button_.corner_radius = get_button_corner_radius(screen);
    button_.border_width = get_button_border_width(screen);
    button_.width = screen_w * 0.18f * 1.15f * ProductionInterface::kHeightWidthBestRatio;

    button_.height = screen_h * 0.07f;

    button_.set_pos({pos.x + background_width * 0.375f, pos.y - screen_h * 0.07f / 2});

    button_.background_color = ProductionSlots::kButtonBackgroundColor;
    button_.text.color = ProductionSlots::kButtonTextColor;
    button_.text.size = ProductionSlots::get_button_text_size(screen);
}

const Color ProductionSlots::kButtonBackgroundColor = {247, 247, 247};
const Color ProductionSlots::kButtonTextColor = {116, 116, 116};

void ProductionSlots::update(Barrack* barrack) {
    barrack_ = barrack;

}

void ProductionSlots::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(barrack_ != nullptr);
    DrawButtonsByStats(screen, game_options, barrack_->get_player().get_factories_stats().units_production_stats);
}

void ProductionSlots::add_to_pos(const Vector2D& transition) {
    production_image_.position += transition;
    cost_text_.position += transition;
    button_.add_to_pos(transition);
}