#include "a_star.h"

bool is_valid(const vector<vector<int>>& grid, const Pair& point, int col, int row) {
	return (point.first >= 0) && (point.first < row) && (point.second >= 0) && (point.second < col);
}

