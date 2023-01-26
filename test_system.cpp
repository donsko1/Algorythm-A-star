#include "a_star.h"
#include <time.h>
#include <string>
#include <stdio.h>


void manual_check(int test_num) {
    string file_name = "tests//input.txt";
    string file_answer = "tests//result.txt";
    ifstream finput(file_name.insert(6, to_string(test_num)));
    ifstream fcorrect(file_answer.insert(6, to_string(test_num)));

    int row, col, start_x, start_y, end_x, end_y, count = 0;
    unsigned long long int ga = 0, gd = 0, gc;
    vector<Pair> va, vd;

    finput >> row >> col >> start_x >> start_y >> end_x >> end_y;
    fcorrect >> gc;

    Pair start(start_y, start_x);
    Pair end(end_y, end_x);

    vector< vector <int> > grid(row, vector<int>(col));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            finput >> grid[i][j];
        }
    }
    va = A_star(grid, start, end, false);
    vd = Dijkstra(grid, start, end);

    for (int i = 0; i < va.size(); ++i) {
        ga += grid[va[i].first][va[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        gd += grid[vd[i].first][vd[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        if (va[i] != vd[i]) {
            count++;
        }
    }

    cout << "Test " << test_num << ":" << endl;

    (gc == ga) ? cout << "Algorithm A*: OK" << endl : cout << "Algorithm A*: WA" << endl;
    
    (gc == gd) ? cout << "Algorithm Dijkstra: OK" << endl : cout << "Algorithm Dijkstra: WA" << endl;

    cout << "G = " << ga << endl << "difference in path cells " << count  << " from " << va.size() 
         << endl << "===================================" << endl;
}

void rand_check(int test_num) {
    srand(time(NULL) + test_num);

    int col = 1 + rand() % (100 - 1 + 1);
    int row = 1 + rand() % (100 - 1 + 1);
    int start_x = 0 + rand() % (col - 1 + 1);
    int start_y = 0 + rand() % (row - 1 + 1);
    int end_x = 0 + rand() % (col - 1 + 1);
    int end_y = 0 + rand() % (row - 1 + 1);
    

    vector< vector <int> > grid(row, vector<int>(col));
    Pair start(start_y, start_x);
    Pair end(end_y, end_x);
    vector<Pair> va, vd;
    unsigned long long int ga = 0, gd = 0, count = 0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            grid[i][j] = 1 + rand() % (1000000 - 1 + 1);
        }
    }

    va = A_star(grid, start, end, false);
    vd = Dijkstra(grid, start, end);

    for (int i = 0; i < va.size(); ++i) {
        ga += grid[va[i].first][va[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        gd += grid[vd[i].first][vd[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        if (va[i] != vd[i]) 
            count++;
    }
    
    (ga == gd) ? cout << "Test " << test_num << ": OK" << endl << "G = " << ga << endl : cout << "Test " << test_num << ": WA" << endl;
    
    cout << "difference in path cells " << count << " from " << va.size() << endl << "===================================" << endl;
}

void one_value_check(int col, int row, int start_x, int start_y, int end_x, int end_y, int value, int test_num) {
    vector< vector <int> > grid(row, vector<int>(col, value));
    Pair start(start_y, start_x);
    Pair end(end_y, end_x);
    vector<Pair> va, vd;
    unsigned long long int ga = 0, gd = 0, count = 0;

    va = A_star(grid, start, end, false);
    vd = Dijkstra(grid, start, end);

    for (int i = 0; i < va.size(); ++i) {
        ga += grid[va[i].first][va[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        gd += grid[vd[i].first][vd[i].second];
    }
    for (int i = 0; i < vd.size(); ++i) {
        if (va[i] != vd[i])
            count++;
    }

    (ga == gd) ? cout << "Test " << test_num << ": OK" << endl << "G = " << ga << endl : cout << "Test " << test_num << ": WA" << endl;

    cout << "difference in path cells " << count << " from " << va.size() << endl << "===================================" << endl;
}

void test() {
        for (int i = 1; i <= 10; ++i) {
            manual_check(i);
        }

        one_value_check(100, 200, 0, 0, 99, 199, 1, 11);
        for (int i = 12; i <= 36; ++i) {
            rand_check(i);
        }
        one_value_check(10000, 10000, 0, 0, 9999, 9999, 1, 37);
}