#include "source/drawable_objects_groups/interfaces/unit_production.h"
#include "source/drawable_objects/interface_elements/switch_button.h"
#include "source/drawable_objects_groups/interfaces/building_production_slots.h"

class Town;

class TownProductionInterface : public ProductionInterface {
    BuildingProductionSlots building_slots_;
    SwitchButton unit_and_building_switch_;
    void UpdateSlotsVisibility();
    void UpdateSize() override;
public:
    void set_visible(bool visibility) override;
    void ReClick(SceneInfo& scene);
    explicit TownProductionInterface(const Screen& screen);
    void update(const Town*);
    void Draw(Screen&, const GameOptions&) override;
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
};
