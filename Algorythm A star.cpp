#include "a_star.h"

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    bool viz = false;
    unsigned long int row, col, start_x, start_y, end_x, end_y;
    fin >> row >> col >> start_x >> start_y >> end_x >> end_y;

    Pair start(start_x, start_y);
    Pair end(end_x, end_y);

    vector< vector <int> > grid(row);

    for (int i = 0; i < row; ++i) {
        grid[i].resize(col);
        for (int j = 0; j < col; ++j) {
            fin >> grid[i][j];
        }
    }

    cout << "With visualization - 1" << endl << "Testing system - 0" << endl << "Your choice: ";
    cin >> viz;
    system("cls");

    A_star(grid, start, end, col, row, viz);

}

