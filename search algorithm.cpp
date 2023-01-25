#include "a_star.h"

int heuristic(const Pair& current, const Pair& end) {
    return sqrt(
        (current.first - end.first) * (current.first - end.first) +
        (current.second - end.second) * (current.second - end.second));
}

bool is_valid(const vector<vector<int>>& grid, const Pair& point, int col, int row) {
    return (point.first >= 0) && (point.first < row) && (point.second >= 0) && (point.second < col);
}

unsigned long long int A_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, bool visualization){
    int row = grid.size();
    int col = grid[0].size();
    long long int g_o = 0;

    vector< vector <bool> > closed_list(row, vector<bool>(col, false));
    vector< vector <cell> > cell_details(row, vector<cell>(col));

    Pair path_pair;
    Pair start = current;

    int i = current.first, j = current.second;
    cell_details[i][j].f = 0;
    cell_details[i][j].g = 0;
    cell_details[i][j].h = 0;
    cell_details[i][j].parent = { i, j };

    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> open_list;
    open_list.emplace(0, i, j);

    while (!open_list.empty()) {
        const Tuple& p = open_list.top();
        i = get<1>(p);
        j = get<2>(p);
        open_list.pop();
        closed_list[i][j] = true;

        if(visualization)
            draw(grid, closed_list, end);

        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                //n - соседн€€ €чейка 
                Pair n(i + x, j + y);

                if (is_valid(grid, n, col, row)) {
                    if (n == end) {
                        cell_details[n.first][n.second].parent = { i, j };
                        g_o = path_making(cell_details, grid, start, end, visualization);
                        return g_o;
                    }
                    else if (!closed_list[n.first][n.second] || 
                                cell_details[i][j].g + grid[n.first][n.second] < 
                                    cell_details[n.first][n.second].g) {
                        double g_new, h_new, f_new;
                        g_new = cell_details[i][j].g + grid[n.first][n.second];
                        h_new = heuristic(n, end);
                        f_new = g_new + h_new;

                        if (cell_details[n.first][n.second].f == -1 || 
                                cell_details[n.first][n.second].f > f_new) {
                            path_pair = { i, j };
                            open_list.emplace(f_new, n.first, n.second);
                            cell_details[n.first][n.second].g = g_new;
                            cell_details[n.first][n.second].h = h_new;
                            cell_details[n.first][n.second].f = f_new;
                            cell_details[n.first][n.second].parent = { i, j };
                        }
                    }
                }
            }
        }
    }
}

unsigned long long int Dijkstra(const vector<vector<int>>& grid, const Pair& current, const Pair& end) {
    int row = grid.size();
    int col = grid[0].size();
    long long int g_o = 0;

    vector< vector <bool> > closed_list(row, vector<bool>(col, false));
    vector< vector <cell> > cell_details(row, vector<cell>(col));

    Pair path_pair;
    Pair start = current;

    int i = current.first, j = current.second;
    cell_details[i][j].f = 0;
    cell_details[i][j].g = 0;
    cell_details[i][j].parent = { i, j };

    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> open_list;
    open_list.emplace(0, i, j);

    while (!open_list.empty()) {
        const Tuple& p = open_list.top();
        i = get<1>(p);
        j = get<2>(p);
        open_list.pop();
        closed_list[i][j] = true;

        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                //n - соседн€€ €чейка 
                Pair n(i + x, j + y);

                if (is_valid(grid, n, col, row)) {
                    if (n == end) {
                        cell_details[n.first][n.second].parent = { i, j };
                        g_o = path_making(cell_details, grid, start, end, false);
                        return g_o;
                    }
                    else if (!closed_list[n.first][n.second] ||
                        cell_details[i][j].g + grid[n.first][n.second] <
                        cell_details[n.first][n.second].g) {
                        double g_new, f_new;
                        g_new = cell_details[i][j].g + grid[n.first][n.second];
                        f_new = g_new;

                        if (cell_details[n.first][n.second].f == -1 ||
                            cell_details[n.first][n.second].f > f_new) {
                            path_pair = { i, j };
                            open_list.emplace(f_new, n.first, n.second);
                            cell_details[n.first][n.second].g = g_new;
                            cell_details[n.first][n.second].f = f_new;
                            cell_details[n.first][n.second].parent = { i, j };
                        }
                    }
                }
            }
        }

    }
}
