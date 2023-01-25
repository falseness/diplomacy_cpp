#include <vector>
#include <tuple>

#include "source/drawable_objects_groups/game_scene/grid/action.h"


using std::vector;
class Entity;
class Grid;

class UndoButton {
    vector<std::pair<GridAction*, optional<SelectedEntity>>> undo_actions_stack_;
    static optional<SelectedEntity> InitializeSelectedEntity(const Entity* entity, const Grid& grid);
public:
    void AddAction(GridAction& action, const Entity* entity, const Grid& grid);
    inline void Clear() {
        undo_actions_stack_.clear();
    }
};