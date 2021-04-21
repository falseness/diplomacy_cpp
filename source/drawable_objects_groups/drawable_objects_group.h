#include <source/drawable_objects/sprite.h>
#include <source/sfml_facades/screen.h>
#include <source/options/options.h>
#include <vector>
#include <source/utility/all_usings.h>

#pragma once

class DrawableObjectsGroup : public DrawableObject {
protected:
    std::vector<DrawableObject*> drawable_objects_;
public:
    virtual void Draw(Screen& screen, const GameOptions&);
    //void HandleEvent() {}
};
