#include "unit.h"
#include "source/drawable_objects/cell/coord_converter.h"
#include "source/drawable_objects/cell/cell.h"
#include "source/drawable_objects_groups/game_scene/grid/grid.h"
#include "source/drawable_objects/unit/unit_logic.h"
#include "source/drawable_objects_groups/game_scene/game_scene.h"
#include "source/drawable_objects/hittable_entity.h"

const UnitStats& Unit::get_stats() const {
    auto it = get_player_stats().units.find(image_name_);
    assert(it != get_player_stats().units.end());
    return it->second;
}

Unit::Unit(Cell* cell, std::string image_name) : Entity(cell, std::move(image_name)) {
    const UnitStats& unit_type_stats = get_stats();
    hp_ = unit_type_stats.hp;
    dmg_ = unit_type_stats.dmg;
    moves_ = unit_type_stats.speed;
    salary_ = unit_type_stats.salary;
}

void Unit::set_cell(Cell* cell) {
    if (!cell->IsStore(this))
        assert(false);
    cell_ = cell;
}

ClickResponse Unit::HandleClick(SceneInfo& scene, const Vector2D &click_pos, const GameOptions &game_options) const {
    scene.selection_border.Clear();
    std::pair<int, int> coord = CoordConverter::CalculateCoord(click_pos, game_options);
    if (scene.grid.is_coord_out_of_range(coord)) {
        scene.entity_interface.set_visible(false);
        return {true, false, false};
    }

    if (!is_my_turn()) {
        scene.entity_interface.set_visible(false);
        return {true, coord != get_coord(), coord == get_coord()};
    }

    ClickResponse click_response = ClickLogic(scene, coord);
    if (click_response.should_remove_selection)
        scene.entity_interface.set_visible(false);
    return click_response;
}

ClickResponse Unit::ClickLogic(SceneInfo &scene, std::pair<int, int> &coord) const {
    ClickResponse click_response = UnitLogic::kUnitLogic.ClickLogic(*this, scene.grid, coord);
    return click_response;
}

unsigned int Unit::get_moves() const {
    return moves_;
}

void Unit::Select(const SceneInfo& scene) const {
    UnitLogic::kUnitLogic.Select(scene, *this, is_my_turn() ? get_moves() : get_speed());
    Entity::Select(scene);
}


void Unit::MoveTo(Grid& grid, std::pair<int, int> coord) const {
    grid.DecreaseUnitMoves(get_coord(), grid.logic_helper_.get_info(coord));

    std::vector<std::pair<int, int>> path;
    auto this_coord = coord;
    while (this_coord != get_coord()) {
        path.push_back(this_coord);
        this_coord = grid.logic_helper_.get_parent(this_coord);
    }
    reverse(path.begin(), path.end());
    for (auto next_coord : path) {
        auto current_cell = grid.get_cell(get_coord());
        auto cell = grid.get_cell(next_coord);
        if (cell->is_hittable(get_player_index())) {
            cell->HitSomethingOnCell(dmg_, grid);
            assert(next_coord == path.back());
        }

        if (cell->is_passable(get_player_index())) {
            if (!cell->is_my_turn() && !cell->get_building()->is_empty())
                grid.DeleteBuilding(cell->get_coord());
            current_cell->MoveUnitTo(*cell, grid);
            continue;
        }
    }
}

json Unit::to_json() {
    auto result = Entity::to_json();
    result["hp"] = hp_;
    result["moves"] = moves_;
    return std::move(result);
}

json Unit::get_info() const {
    auto result = HittableEntity::get_info();
    result["info"]["dmg"] = dmg_;
    if (is_my_turn())
        result["info"]["moves"] = std::to_string(moves_) + " / " + std::to_string(get_speed());
    else
        result["info"]["speed"] = std::to_string(get_speed());
    result["info"]["salary"] = std::to_string(salary_);
    return std::move(result);
}

unsigned int Unit::get_speed() const {
    return get_stats().speed;
}

unsigned int Unit::get_maximum_hp() const {
    return get_stats().hp;
}

void Unit::NextTurn(SceneInfo&) {
    moves_ = get_speed();
    get_player().IncreaseGold(-salary_);
}

bool Unit::is_passable(size_t asking_player_index) const {
    return false;
}

void Unit::Kill(Grid& grid) const {
    grid.DeleteUnit(get_coord());
}

void Unit::AskGridToDecreaseHP(int dmg, Grid &grid) const {
    grid.DecreaseUnitHP(get_coord(), dmg);
}

bool Unit::is_attackable(const Cell &cell) const {
    return cell.is_hittable(get_player_index());
}

bool Unit::can_melee_interact(const Cell &cell) const {
    return cell.is_passable(get_player_index()) || cell.is_hittable(get_player_index());
}

bool Unit::is_on_high_ground() const {
    return get_cell()->get_building()->is_high_ground();
}

bool EmptyUnit::is_passable(size_t asking_player_index) const {
    return true;
}

EmptyUnit::EmptyUnit(Cell* cell) : Unit(cell, std::string(Entity::kEmptyEntityName)),
    Entity(cell, std::string(Entity::kEmptyEntityName)) {}

void EmptyUnit::Draw(Screen &, const GameOptions &) {}

void EmptyUnit::Select(const SceneInfo&) const {}

bool EmptyUnit::is_hittable(size_t asking_player_index) const {
    return false;
}
