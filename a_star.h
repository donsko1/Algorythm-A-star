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
/*
struct Pair {
int first;
int second;
Pair(int _x, int _y) {
this->first = _x;
this->second = _y;
}
Pair() {
first = 0;
second = 0;
}

bool operator == (Pair& a, const Pair& b) {
return a == b;
}
};
*/

unsigned long long int A_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, bool visualization);

unsigned long long int Dijkstra(const vector<vector<int>>& grid, const Pair& current, const Pair& end);

void draw(const vector<vector<int>>& grid, const vector<vector<bool>>& path, const Pair& end);

unsigned long long int path_making(vector<vector<cell>>& cell_details, const vector<vector<int>>& grid,
                const Pair& start, const Pair& end, bool visualization);

void test();