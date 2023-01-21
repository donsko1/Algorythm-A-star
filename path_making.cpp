#include "a_star.h"

int path_making(vector<vector<cell>>& cell_details, const vector<vector<int>>& grid, 
                const Pair& start, const Pair& end, bool visualization) {
    int row = grid.size();
    int col = grid[0].size();

    stack<Pair> path;
    vector<Pair>path_pair;
    int g = 0;
    int rows = end.first;
    int cols = end.second;
    Pair next_node = cell_details[rows][cols].parent;

    do {
        path.push(next_node);
        path_pair.push_back(next_node);
        next_node = cell_details[rows][cols].parent;
        rows = next_node.first;
        cols = next_node.second;
    } while (cell_details[rows][cols].parent != next_node);

    if (visualization) {
        ofstream fout("output.txt");
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {

                cout << setiosflags(ios::left);

                if (i == start.first && j == start.second) {
                    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hwnd, BACKGROUND_BLUE | BACKGROUND_GREEN |
                        BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                }
                if (i == end.first && j == end.second) {
                    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hwnd, BACKGROUND_BLUE | BACKGROUND_GREEN |
                        BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
                }
                for (int q = 0; q < path.size(); ++q) {
                    if (i == path_pair[q].first && j == path_pair[q].second) {
                        HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hwnd, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE);
                    }
                }

                cout << setw(4) << grid[i][j] << " ";

                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            cout << endl;
        }

        cout << "Path found";

        path.emplace(rows, cols);
        while (path.size() != 1) {
            Pair p = path.top();
            path.pop();
            cout << endl << "(" << p.first << ";" << p.second << ")";
            g += grid[p.first][p.second];
        }
        g += grid[end.first][end.second];
        cout << endl << "(" << end.first << ";" << end.second << ")" << endl << "The cost of the path is " << g;
        fout << g;

        fout.close();
    }
    else {
        path.emplace(rows, cols);
        while (path.size() != 1) {
            Pair p = path.top();
            path.pop();
            g += grid[p.first][p.second];
        }
        g += grid[end.first][end.second];
        //cout << g;
        //fout << g;

        //fout.close();
        return g;
    }
}
