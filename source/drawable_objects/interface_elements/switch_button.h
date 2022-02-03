#include <source/drawable_objects/interface_elements/rounded_rectangle.h>
#include <source/drawable_objects/interface_elements/text.h>

struct SwitchButton : public RoundedRectangle {
    Text left_text;
    Text right_text;
    bool is_left_selected = true;
    void update_texts_position(Screen& screen);
    void do_switch();
    void set_text_size(size_t);
    Text& get_selected_text();
    void Draw(Screen&, const GameOptions&) override;
};