#include "a_star.h"
#include <time.h>
#include <string>

void manual_check(ifstream &finput, ifstream &fcorrect, int test_num) {
    unsigned long int row, col, start_x, start_y, end_x, end_y, ga, gc;
    finput >> row >> col >> start_x >> start_y >> end_x >> end_y;
    fcorrect >> gc;

    Pair start(start_y, start_x);
    Pair end(end_y, end_x);

    vector< vector <int> > grid(row);
    for (int i = 0; i < row; ++i) {
        grid[i].resize(col);
        for (int j = 0; j < col; ++j) {
            finput >> grid[i][j];
        }
    }
    ga = A_star(grid, start, end, false);
    if (ga == gc)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
}

void auto_check(ifstream& finput, int test_num) {
    unsigned long int row, col, start_x, start_y, end_x, end_y, ga, gd;
    finput >> row >> col >> start_x >> start_y >> end_x >> end_y;

    Pair start(start_y, start_x);
    Pair end(end_y, end_x);

    vector< vector <int> > grid(row);
    for (int i = 0; i < row; ++i) {
        grid[i].resize(col);
        for (int j = 0; j < col; ++j) {
            finput >> grid[i][j];
        }
    }
    ga = A_star(grid, start, end, false);
    gd = Dijkstra(grid, start, end);
    if (ga == gd)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
}

void grid_make_check(int col, int row, int start_x, int start_y, int end_x, int end_y, int value, int test_num) {
    vector< vector <int> > grid(row, vector<int>(col, value));
    Pair start(start_y, start_x);
    Pair end(end_y, end_x);
    unsigned long int ga, gd;
    if (value == 0) {
        srand(time(NULL));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                grid[i][j] = 1 + rand() % (1000000 - 1 + 1);
            }
        }
    }
    ga = A_star(grid, start, end, false);
    gd = Dijkstra(grid, start, end);
    if (ga == gd)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
}


void test() {
    {
        for (int i = 1; i <= 1; ++i) {
            string file_name = "tests\\\\input.txt";
            string file_answer = "tests\\\\result.txt";
            file_name.insert(6, to_string(i));
            file_answer.insert(6, to_string(i));
            ifstream finput(file_name);
            ifstream fcorrect(file_answer);
            manual_check(finput, fcorrect, i);
            finput.close();
            fcorrect.close();
        }
        //return;
    }
    
    {
        grid_make_check(10, 10, 0, 0, 9, 9, 0, 3);
    }

    {
        ifstream finput("tests\\6\\input.txt");
        auto_check(finput, 6);
        finput.close();
    }
}