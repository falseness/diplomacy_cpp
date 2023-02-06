#include "source/drawable_objects/building/suburb_building.h"
#include "source/player/entity_stats.h"
#include "source/player/factories/entity.h"

#pragma once

class Barrack : virtual public SuburbBuilding {
    ProductionInfo production_;
    bool production_in_progress_ = false;
    static constexpr float kProductionDrawOpacity = 0.7;
protected:
    virtual void set_production_interface_visible(const SceneInfo& scene, bool) const;
    virtual void UpdateProductionInterface(const SceneInfo& scene) const;
    virtual void SelectionProductionInterface(const SceneInfo& scene) const;
public:
    [[nodiscard]] unsigned int get_turns_left() const;
    [[nodiscard]] bool is_production_in_progress() const;
    [[nodiscard]] std::string get_training_unit_name() const;
    void StartProduction(ProductionInfo);
    void UndoStartedProduction();
    Barrack(Cell* cell, std::string image_name);
    ClickResponse HandleClick(SceneInfo&, const Vector2D&, const GameOptions&) const override;
    void Select(const SceneInfo&) const override;
    void NextTurn(SceneInfo& scene) override;
    [[nodiscard]] json get_info() const override;
    void Draw(Screen&, const GameOptions&) override;
};