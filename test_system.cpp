#include "a_star.h"
#include <time.h>

void manual_check(ifstream &finput, ifstream &fcorrect, int test_num) {
    ifstream fanswer("output.txt");
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
    A_star_n(grid, start, end, col, row);
    fanswer >> ga;
    if (ga == gc)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
    fanswer.close();
}

void auto_check(ifstream& finput, int test_num) {
    ifstream fanswer("output.txt");
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
    A_star_n(grid, start, end, col, row);
    fanswer >> ga;
    fanswer.close();
    ifstream fdanswer("output.txt");
    Dijkstra(grid, start, end, col, row);
    fdanswer >> gd;
    if (ga == gd)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
    fanswer.close();
    fdanswer.close();
}

void grid_make_check(int col, int row, int start_x, int start_y, int end_x, int end_y, int value, int test_num) {
    ifstream fanswer("output.txt");
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
    A_star_n(grid, start, end, col, row);
    fanswer >> ga;
    fanswer.close();
    ifstream fdanswer("output.txt");
    Dijkstra(grid, start, end, col, row);
    fdanswer >> gd;
    if (ga == gd)
        cout << "test " << test_num << ": OK";
    else
        cout << "test " << test_num << ": WA";
    cout << endl;
    fanswer.close();
    fdanswer.close();
}

void test() {
    {
        ifstream finput("tests\\1\\input.txt");
        ifstream fcorrect("tests\\1\\result.txt");
        manual_check(finput, fcorrect, 1);
        finput.close();
        fcorrect.close();
    }

    {
        ifstream finput("tests\\2\\input.txt");
        ifstream fcorrect("tests\\2\\result.txt");
        manual_check(finput, fcorrect, 2);
        finput.close();
        fcorrect.close();
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