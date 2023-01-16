#include "a_star.h"

void A_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, int col, int row, bool viz){
    vector< vector <bool> > closed_list(row, vector<bool>(col, false));
    vector< vector <cell> > cell_details(row, vector<cell>(col));

    vector<Pair>path;
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

        if (viz) {
            draw(grid, path, end, row, col);
            Sleep(10);
            system("cls");
        }

        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                Pair neighbour(i + x, j + y);

                if (is_valid(grid, neighbour, col, row)) {
                    if (neighbour == end) {
                        cell_details[neighbour.first][neighbour.second].parent = { i, j };
                        path_making(cell_details, grid, start, end, col, row);
                        return;
                    }
                    else if (!closed_list[neighbour.first][neighbour.second] || 
                                cell_details[i][j].g + grid[neighbour.first][neighbour.second] < 
                                    cell_details[neighbour.first][neighbour.second].g) {
                        double g_new, h_new, f_new;
                        g_new = cell_details[i][j].g + grid[neighbour.first][neighbour.second];
                        h_new = heuristic(neighbour, end);
                        f_new = g_new + h_new;

                        if (cell_details[neighbour.first][neighbour.second].f == -1 || 
                                cell_details[neighbour.first][neighbour.second].f > f_new) {
                            path_pair = { i, j };
                            path.push_back(path_pair);
                            open_list.emplace(f_new, neighbour.first, neighbour.second);
                            cell_details[neighbour.first][neighbour.second].g = g_new;
                            cell_details[neighbour.first][neighbour.second].h = h_new;
                            cell_details[neighbour.first][neighbour.second].f = f_new;
                            cell_details[neighbour.first][neighbour.second].parent = { i, j };
                        }
                    }
                }
            }
        }

    }
}
