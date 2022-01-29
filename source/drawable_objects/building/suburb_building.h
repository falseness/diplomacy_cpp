#include <source/drawable_objects/building/building.h>

class SuburbBuildingStats;

class SuburbBuilding : virtual public Building {
public:
    const SuburbBuildingStats& get_stats() const;
    SuburbBuilding(const Cell* cell, std::string&& image_name);
    ~SuburbBuilding() override = default;
    int get_income() const;
    json get_info() const override;
};