#include <source/drawable_objects_groups/interfaces/production.h>
#include <source/drawable_objects/interface_elements/switch_button.h>

class Town;

class TownProductionInterface : public ProductionInterface {
    SwitchButton unit_and_building_switch_;
public:
    explicit TownProductionInterface(const Screen& screen);
    void update(Town*);
};
