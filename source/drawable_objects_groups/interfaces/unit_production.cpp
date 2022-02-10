#include "unit_production.h"
#include <source/drawable_objects/building/barrack.h>
#include <cassert>


ProductionInterface::ProductionInterface(const Screen &screen) : production_slots_(nullptr) {
    visible_ = false;

    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = w * 0.03f * 1.15f;

    Vector2D pos(w * 0.68f, h * 0.01f);

    this_height = h * 0.4f;
    this_width = w - pos.x;

    background_.set_pos(Vector2D(pos.x, pos.y));
    background_.height = this_height;
    background_.width = this_width + corner_radius;
    background_.corner_radius = corner_radius;
    background_.background_color = Color(0, 255, 00);



    gold_image_.position.x = pos.x + w * 0.22f * 0.17f * 1.15f;
    gold_image_.position.y = pos.y + this_height * 0.13f;
    gold_image_.name = "gold";
    gold_image_.size = {this_height * 0.25f, this_height * 0.25f};

    gold_text_.position = {gold_image_.position.x + w * 0.22f * 1.15f * 0.92f, gold_image_.position.y};
    gold_text_.size = static_cast<size_t>(w * 1.15f * 0.03f);


    production_slots_ = std::make_unique<ProductionSlots>(get_slots_pos(screen), this_width, this_height, screen);


    drawable_objects_.push_back(&background_);
    drawable_objects_.push_back(&gold_image_);
    drawable_objects_.push_back(&gold_text_);
    drawable_objects_.push_back(production_slots_.get());
}

Vector2D ProductionInterface::get_slots_pos(const Screen& screen) const {
    auto margin = get_margin_between_gold_image_and_slots(screen);
    return {gold_image_.position.x , background_.get_up() + gold_image_.size.height + margin};
}

void ProductionInterface::update(Barrack* barrack) {
    barrack_ = barrack;
    production_slots_->update(barrack);
    background_.background_color = barrack_->get_color();
    UpdateSize();
}


ProductionInterface::ProductionSlots::ProductionSlots(Vector2D pos, float background_width, float background_height,
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

const Color ProductionInterface::ProductionSlots::kButtonBackgroundColor = {247, 247, 247};
const Color ProductionInterface::ProductionSlots::kButtonTextColor = {116, 116, 116};

void ProductionInterface::ProductionSlots::update(Barrack* barrack) {
    barrack_ = barrack;

}

void ProductionInterface::ProductionSlots::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(barrack_ != nullptr);
    DrawButtonsByStats(screen, game_options, barrack_->get_player().get_factories_stats().units_production_stats);
}

void ProductionInterface::ProductionSlots::add_to_pos(const Vector2D& transition) {
    production_image_.position += transition;
    cost_text_.position += transition;
    button_.add_to_pos(transition);
}


const float ProductionInterface::kHeightWidthBestRatio = 0.55f;

void ProductionInterface::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(barrack_ != nullptr);
    gold_text_.text = std::to_string(barrack_->get_player().get_gold());
    DrawableObjectsGroup::Draw(screen, game_options);
}

bool ProductionInterface::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) {
    if (!visible_ || !background_.is_inside(click_pos))
        return false;
    production_slots_->HandleClick(scene, click_pos, game_options);
    return true;
}

float ProductionInterface::get_margin_between_gold_image_and_slots(const Screen& screen) {
    return static_cast<float>(screen.get_height()) * 0.14f;
}

float ProductionInterface::get_center_x() const {
    return background_.get_center_x() - background_.corner_radius / 2;
}

float ProductionInterface::get_width() const {
    return background_.width - background_.corner_radius / 2;
}

void ProductionInterface::UpdateSize() {

    background_.height = production_slots_->get_bottom() - background_.up_side_y;
}


bool ProductionInterface::ProductionSlots::HandleClick(SceneInfo& scene, const Vector2D& pos,
                                                       const GameOptions &game_options) {
    if (!visible_)
        return false;
    assert(barrack_ != nullptr);

    if (!can_start_new_production())
        return false;

    const auto& factories = barrack_->get_player().get_factories_stats();
    return CheckButtonsClick(pos, scene, factories);
}

const std::string ProductionInterface::ProductionSlots::kCostTextStart = "cost: ";

void ProductionInterface::ProductionSlots::set_button_text(const std::pair<std::string, EntityProductionStats>& stat) {
    static const std::string kTrainButtonText = "train";
    assert(barrack_ != nullptr);
    if (!barrack_->is_production_in_progress()) {
        button_.text.text = kTrainButtonText;
        return;
    }

    if (is_should_display_button(stat)) {
        button_.text.text = std::to_string(barrack_->get_turns_left()) + "/" + std::to_string(stat.second.turns);
    }
}

bool ProductionInterface::ProductionSlots::is_should_display_button(
        const std::pair<std::string, EntityProductionStats>& stat) const {
    assert(barrack_ != nullptr);
    if (!barrack_->is_production_in_progress())
        return true;
    return stat.first == barrack_->get_training_unit_name();
}

float ProductionInterface::ProductionSlots::get_button_corner_radius(const Screen& screen) {
    return static_cast<float>(screen.get_height()) * 0.03f;
}

float ProductionInterface::ProductionSlots::get_button_border_width(const Screen& screen) {
    return static_cast<float>(screen.get_height()) * 0.003f;
}

size_t ProductionInterface::ProductionSlots::get_button_text_size(const Screen& screen) {
    return static_cast<size_t>(screen.get_width() * 0.04f * 1.15f * ProductionInterface::kHeightWidthBestRatio);
}

bool ProductionInterface::ProductionSlots::CheckButtonsClick(const Vector2D &pos, SceneInfo& scene,
                                                             const PlayersEntitiesFactories& factories) {
    auto stat = get_corresponding_stat(pos, factories.units_production_stats);
    if (stat == factories.units_production_stats.end())
        return false;
    barrack_->StartProduction(ProductionInfo{stat->first, 0});
    barrack_->Select(scene);
    return true;
}

void ProductionInterface::ProductionSlots::DrawButtonsByStats(
        Screen &screen, const GameOptions& game_options, const std::map<std::string, EntityProductionStats>& stats) {
    int i = 0;
    for (auto stat = stats.begin(); stat != stats.end(); ++stat, ++i) {
        production_image_.name = stat->first;
        production_image_.Draw(screen, game_options);

        cost_text_.text = ProductionSlots::kCostTextStart + std::to_string(stat->second.cost);
        cost_text_.Draw(screen, game_options);

        set_button_text(*stat);
        if (is_should_display_button(*stat))
            button_.Draw(screen, game_options);
        add_to_pos(interval_between_);
    }
    add_to_pos(interval_between_ * static_cast<float>(-i));
}

float ProductionInterface::ProductionSlots::get_bottom() const {
    assert(barrack_ != nullptr);
    size_t buttons_count = barrack_->get_player().get_factories_stats().units_production_stats.size();
    return button_.get_bottom() + static_cast<float>(buttons_count) * interval_between_.y;
}

bool ProductionInterface::ProductionSlots::can_start_new_production() const {
    return !barrack_->is_production_in_progress();
}
