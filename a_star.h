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

vector<Pair> A_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, bool visualization);

vector<Pair> Dijkstra(const vector<vector<int>>& grid, const Pair& current, const Pair& end);

void draw(const vector<vector<int>>& grid, const vector<vector<bool>>& path, const Pair& end);

vector<Pair> path_making(vector<vector<cell>>& cell_details, const Pair& start, const Pair& end);

void visualization(vector<Pair>path, const vector<vector<int>>& grid, const Pair& start, const Pair& end);

void test();