#include "unit_production.h"
#include "source/drawable_objects/building/barrack.h"
#include "source/drawable_objects_groups/interfaces/production_slots.h"
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



