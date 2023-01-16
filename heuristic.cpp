#include "a_star.h"

int heuristic(const Pair& current, const Pair& end) {
	return sqrt(
		(current.first - end.first) * (current.first - end.first) +
		(current.second - end.second) * (current.second - end.second));
}