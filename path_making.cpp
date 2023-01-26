#include "a_star.h"

vector<Pair> path_making(vector<vector<cell>>& cell_details,
                const Pair& start, const Pair& end) {
    int row = cell_details.size();
    int col = cell_details[0].size();

    vector<Pair>path_pair;
    int rows = end.first;
    int cols = end.second;
    Pair next_node = end;

    do {
        path_pair.push_back(next_node);
        next_node = cell_details[rows][cols].parent;
        rows = next_node.first;
        cols = next_node.second;
    } while (start != next_node);
    path_pair.push_back(start);
    reverse(path_pair.begin(), path_pair.end());
    return path_pair;
}
