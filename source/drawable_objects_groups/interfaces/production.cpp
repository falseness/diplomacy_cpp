#include "production.h"
#include <source/drawable_objects/building/barrack.h>

ProductionInterface::ProductionInterface(const Screen &screen) : first_button_position_(0, 0),
        production_slots_() {
    visible_ = false;

    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = w * 0.03f * 1.15f;

    Vector2D pos(w * 0.70f, h * 0.01f);

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


    production_slots_ = std::make_unique<ProductionSlots>(
            Vector2D(gold_image_.position.x, pos.y + gold_image_.size.height + this_height * 0.15f),
            this_width, this_height, w, h);

    first_button_position_.y = pos.y + this_height * 0.3f;
    first_button_position_.x = pos.x + w * 0.11f * 1.15f * 0.9f;
    button_.set_pos(first_button_position_);


    drawable_objects_.push_back(&background_);
    drawable_objects_.push_back(&gold_image_);
    drawable_objects_.push_back(production_slots_.get());
}

void ProductionInterface::update(Barrack* barrack) {
    barrack_ = barrack;
    background_.background_color = barrack_->get_color();
    factories_ = &barrack_->get_player().get_factories_stats();
}


ProductionInterface::ProductionSlots::ProductionSlots(Vector2D pos, float background_width, float background_height,
                                                      float screen_w, float screen_h) :
        interval_between_(0, background_height * 0.25f) {
    production_image_.size = {screen_h * 0.1f, screen_h * 0.1f};
    production_image_.position = pos;
    cost_text_.position = {pos.x + screen_w * 0.22f * 1.15f * 0.26f, pos.y};


    cost_text_.size = static_cast<size_t>(screen_w * 0.04f * 1.15f * ProductionInterface::kHeightWidthBestRatio);


    button_.corner_radius = screen_h * 0.03f;
    button_.border_width = screen_h * 0.0015f;
    button_.width = screen_w * 0.18f * 1.15f * ProductionInterface::kHeightWidthBestRatio;

    button_.height = screen_h * 0.07f;

    button_.set_pos({pos.x + background_width * 0.33f, pos.y - screen_h * 0.07f / 2});

    button_.background_color = Color(247, 247, 247);
    button_.text.color = Color(116, 116, 116);
    button_.text.size = static_cast<size_t>(screen_w * 0.04f * 1.15f * ProductionInterface::kHeightWidthBestRatio);
    button_.text.text = "train";

    drawable_objects_.push_back(&production_image_);
    drawable_objects_.push_back(&cost_text_);
    drawable_objects_.push_back(&button_);
}


const float ProductionInterface::kHeightWidthBestRatio = 0.55f;