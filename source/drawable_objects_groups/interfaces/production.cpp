#include "production.h"
#include <source/drawable_objects/building/barrack.h>
#include <iostream>
#include <iomanip>

ProductionInterface::ProductionInterface(const Screen &screen) {
    static const float kHeightWidthBestRatio = 0.55f;
    visible_ = false;

    auto w = static_cast<float>(screen.get_width());
    auto h = static_cast<float>(screen.get_height());
    float corner_radius = w * 0.03f * 1.15f;

    Vector2D pos(w * 0.72f, h * 0.01f);

    float this_height = h * 0.4f;
    float this_width = w - pos.x;

    background_.set_pos(Vector2D(pos.x, pos.y));
    background_.height = this_height;
    background_.width = this_width + corner_radius;
    background_.corner_radius = corner_radius;
    background_.background_color = Color(0, 255, 00);

    button_.corner_radius = h * 0.03f;
    button_.border_width = h * 0.0015f;
    button_.width = w * 0.18f * 1.15f * kHeightWidthBestRatio;
    button_.height = h * 0.07f;
    button_.background_color = Color(247, 247, 247);
    button_.text.color = Color(116, 116, 116);
    button_.text.size = static_cast<size_t>(w * 0.04f * 1.15f);
    button_.text.text = "r";
    std::cout << std::setprecision(5);
    std::cout << button_.text.get_height(screen);
    button_.text.text = "t";
    std::cout << button_.text.get_height(screen);

    drawable_objects_.push_back(&background_);
}

void ProductionInterface::update(Barrack* barrack) {
    barrack_ = barrack;
    background_.background_color = barrack_->get_color();
    factories_ = &barrack_->get_player().get_factories_stats();
}

void ProductionInterface::Draw(Screen& screen, const GameOptions& game_options) {
    DrawableObjectsGroup::Draw(screen, game_options);
    button_.Draw(screen, game_options);
}
