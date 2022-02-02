#include "production.h"
#include <source/drawable_objects/building/barrack.h>
#include <cassert>


ProductionInterface::ProductionInterface(const Screen &screen) : production_slots_(nullptr) {
    visible_ = false;

    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = w * 0.03f * 1.15f;

    Vector2D pos(w * 0.68f, h * 0.01f);

    float this_height = h * 0.4f;
    float this_width = w - pos.x;

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


    production_slots_ = std::make_unique<ProductionSlots>(
            Vector2D(gold_image_.position.x, pos.y + gold_image_.size.height + this_height * 0.15f),
            this_width, this_height, screen);


    drawable_objects_.push_back(&background_);
    drawable_objects_.push_back(&gold_image_);
    drawable_objects_.push_back(&gold_text_);
    drawable_objects_.push_back(production_slots_.get());
}

void ProductionInterface::update(Barrack* barrack) {
    barrack_ = barrack;
    production_slots_->update(barrack);
    background_.background_color = barrack_->get_color();
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


    button_.corner_radius = screen_h * 0.03f;
    button_.border_width = screen_h * 0.0015f;
    button_.width = screen_w * 0.18f * 1.15f * ProductionInterface::kHeightWidthBestRatio;

    button_.height = screen_h * 0.07f;

    button_.set_pos({pos.x + background_width * 0.375f, pos.y - screen_h * 0.07f / 2});

    button_.background_color = Color(247, 247, 247);
    button_.text.color = Color(116, 116, 116);
    button_.text.size = static_cast<size_t>(screen_w * 0.04f * 1.15f * ProductionInterface::kHeightWidthBestRatio);
    button_.text.text = "train";
}

void ProductionInterface::ProductionSlots::update(Barrack* barrack) {
    barrack_ = barrack;

}

void ProductionInterface::ProductionSlots::Draw(Screen &screen, const GameOptions& game_options) {
    if (!visible_)
        return;
    assert(barrack_ != nullptr);
    const auto& factories = barrack_->get_player().get_factories_stats();
    const auto& units_stats = factories.units_production_stats;
    int i = 0;
    for (auto stat = units_stats.begin(); stat != units_stats.end(); ++stat, ++i) {
        production_image_.name = stat->first;
        production_image_.Draw(screen, game_options);

        cost_text_.text = kCostTextStart + std::to_string(stat->second.cost);
        cost_text_.Draw(screen, game_options);
        button_.Draw(screen, game_options);
        add_to_pos(interval_between_);

    }
    add_to_pos(interval_between_ * static_cast<float>(-i));
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

const std::string ProductionInterface::ProductionSlots::kCostTextStart = "cost: ";
