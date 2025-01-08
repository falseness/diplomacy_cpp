#pragma once

#include <cstddef>

#include "source/utility/color.h"
#include "source/utility/vector2d.h"
#include "source/utility/object_size.h"
#include "source/options/hexagon.h"


struct GameOptions {
    HexagonOptions hexagon_options;
    Vector2D hexagon_offset;
    size_t text_size_;
    Vector2D text_offset_;
private:
    ObjectSize image_size_;
public:
    static constexpr float kMaxRadiusSize = 75.f;
    static constexpr std::size_t kMaxFPS = 120;
    [[nodiscard]] inline ObjectSize get_image_size() const {
        return image_size_;
    }
    [[nodiscard]] inline Vector2D get_image_offset() const {
        return {0, 0};
    }
    [[nodiscard]] inline size_t get_text_size() const {
        return text_size_;
    }
    [[nodiscard]] inline Vector2D get_text_offset() const {
        return text_offset_;
    }
    float text_outline_thickness;
    Vector2D draw_offset;
    explicit GameOptions(const float dt);
    float get_correct_in_borders_scale(const float dt) const;
    void ScaleRadius(const float dt);
};
