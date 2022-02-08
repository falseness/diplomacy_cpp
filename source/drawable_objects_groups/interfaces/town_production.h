#include <source/drawable_objects_groups/interfaces/unit_production.h>
#include <source/drawable_objects/interface_elements/switch_button.h>

class Town;

class TownProductionInterface : public ProductionInterface {
    class BuildingProductionSlots : public ProductionSlots {
        std::string last_click_;
        Town* town_ = nullptr;
        bool CheckButtonsClick(const Vector2D& pos, SceneInfo& scene,
                               const PlayersEntitiesFactories& factories) override;
    public:
        void Draw(Screen& screen, const GameOptions&) override;
        BuildingProductionSlots(Vector2D pos, float background_width, float background_height, const Screen&);
        void update(Town* town);
        void ReClick(SceneInfo& scene);
        void UnSelect(SceneInfo&);
        [[nodiscard]] float get_bottom() const override;
    };
    BuildingProductionSlots building_slots_;
    SwitchButton unit_and_building_switch_;
    void update_slots_visibility();
    void UpdateSize() override;
public:
    void ReClick(SceneInfo& scene);
    explicit TownProductionInterface(const Screen& screen);
    void update(Town*);
    void Draw(Screen&, const GameOptions&) override;
    bool HandleClick(SceneInfo&, const Vector2D& click_pos, const GameOptions& game_options) override;
};
