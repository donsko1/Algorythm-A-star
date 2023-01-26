#include "a_star.h"

void draw(const vector<vector<int>>& grid, const vector<vector<bool>>& path, const Pair& end) {
    int row = grid.size();
    int col = grid[0].size();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {

            cout << setiosflags(ios::left);

            if (i == end.first && j == end.second) {
                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            
            if (path[i][j]) {
                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }

            cout << setw(4) << grid[i][j] << " ";

            HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hwnd, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        cout << endl;
    }
    Sleep(50);
    system("cls");
}

void visualization(vector<Pair>path, const vector<vector<int>>& grid,
    const Pair& start, const Pair& end) {
    int row = grid.size();
    int col = grid[0].size();
    unsigned long long int g = 0;

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
                if (i == path[q].first && j == path[q].second) {
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

    for (int i = 0; i < path.size(); i++) {
        cout << endl << "(" << path[i].first << ";" << path[i].second << ")";
        g += grid[path[i].first][path[i].second];
    }
    cout << endl << "The cost of the path is " << g;
}