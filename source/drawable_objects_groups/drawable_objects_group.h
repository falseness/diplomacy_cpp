#include <source/drawable_objects/drawable_object.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>
#include <vector>

#pragma once

class DrawableObjectsGroup : public DrawableObject {
protected:
    std::vector<DrawableObject*> drawable_objects_;
    bool visible_ = true;
public:
    void set_visible(bool);
    virtual void Draw(Screen& screen, const GameOptions&);
    //void HandleEvent() {}
};
