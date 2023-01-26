#include "source/player/factories/entity.h"
#include "source/drawable_objects/cell/cell.h"


template <typename UnitType>
class RangeUnitFactory : public UnitFactory {
public:
    void Create(Cell*, const ProductionInfo& production) const override;
    RangeUnitFactory(PlayersEntitiesFactories&, std::string);
};

template <typename UnitType>
void RangeUnitFactory<UnitType>::Create(Cell* cell, const ProductionInfo& production) const {
    cell->template CreateUnit<UnitType>(std::string(production.name));
}

template <typename UnitType>
RangeUnitFactory<UnitType>::RangeUnitFactory(PlayersEntitiesFactories& all_factories, std::string unit_name) :
        UnitFactory(all_factories, std::move(unit_name)) {}