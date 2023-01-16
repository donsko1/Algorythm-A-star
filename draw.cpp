#include "a_star.h"

void draw(const vector<vector<int>>& grid, vector<Pair>path, const Pair& end, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {

            cout << setiosflags(ios::left);

            if (i == end.first && j == end.second) {
                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            for (int q = 0; q < path.size(); ++q) {
                if (i == path[q].first && j == path[q].second) {
                    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                }
            }

            cout << setw(4) << grid[i][j] << " ";

            HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hwnd, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        cout << endl;
    }
}