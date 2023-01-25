#include "cells.h"

#include "source/drawable_objects/cell/cell.h"


bool GridCells::is_coord_out_of_range(std::pair<int, int> coord) const {
    return CoordConverter::IsCoordOutOfRange(coord, cells_.size(), cells_[0].size());
}
