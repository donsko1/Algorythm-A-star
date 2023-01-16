#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <Windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <tuple>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

typedef pair <int, int> Pair;
typedef tuple <double, int, int> Tuple;
struct cell {
    Pair parent;
    double f, g, h;
    cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
};

void A_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, int col, int row, bool viz);

bool is_valid(const vector<vector<int>>& grid, const Pair& point, int col, int row);

int heuristic(const Pair& current, const Pair& end);

void draw(const vector<vector<int>>& grid, vector<Pair>path, const Pair& end, int row, int col);

void path_making(vector<vector<cell>>& cell_details, const vector<vector<int>>& grid,
                const Pair& start, const Pair& end, int col, int row);