#include <iostream>
#include <fstream>
#include <stack>
#include <array>
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

//Проверка на нахождение ячейки внутри поля
bool is_valid(const vector<vector<int>>& grid, const Pair& point, int col, int row) {
    if (row > 0 && col > 0)
        return (point.first >= 0) && (point.first < row) && (point.second >= 0) && (point.second < col);
    return false;
}

//Структура для хранения данных о ячейке
struct cell {
    Pair parent;
    double f, g, h;
    cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
    //double f() { return g + h; }
};

//Проверка на достижение цели
bool check_win(const Pair& current, const Pair& end) {
    return current == end;
}

//Расчет эвристики h
int heuristic(const Pair& current, const Pair& end) {
    return sqrt(
        (current.first - end.first) * (current.first - end.first) +
        (current.second - end.second) * (current.second - end.second));
}

//Отрисовка посещенных ячеек
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

//Отрисовка конечного пути
void path_making(vector<vector<cell>>& cell_details, const vector<vector<int>>& grid, const Pair& start, const Pair& end, int col, int row) {
    stack<Pair> path;
    vector<Pair>path_pair;
    int g = 0;
    int rows = end.first;
    int cols = end.second;
    Pair next_node = cell_details[rows][cols].parent;
    ofstream fout("output.txt");

    do {
        path.push(next_node);
        path_pair.push_back(next_node);
        next_node = cell_details[rows][cols].parent;
        rows = next_node.first;
        cols = next_node.second;
    } while (cell_details[rows][cols].parent != next_node);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {

            cout << setiosflags(ios::left);

            if (i == start.first && j == start.second) {
                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            if (i == end.first && j == end.second) {
                HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hwnd, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
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

void a_star(const vector<vector<int>>& grid, const Pair& current, const Pair& end, int col, int row) {
    ofstream fout("output.txt");
    //Если начало не в диапазоне поля
    if (!is_valid(grid, current, col, row)) {
        cout << "Incorrect data";
        fout << "0";
        return;
    }

    //Если конец не в диапазоне поля
    if (!is_valid(grid, end, col, row)) {
        cout << "Incorrect data";
        fout << "0";
        return;
    }

    //Если начало совпадает с концом
    if (check_win(current, end)) {
        cout << "The beginning matches the end";
        fout << "0";
        return;
    }

    fout.close();

    vector< vector <bool> > closed_list(row);
    for (int i = 0; i < row; ++i) {
        closed_list[i].resize(col);
        for (int j = 0; j < col; ++j)
            closed_list[i][j] = false;
    }
    vector< vector <cell> > cell_details(row);
    for (int i = 0; i < row; ++i) {
        cell_details[i].resize(col);
    }

    vector<Pair>path;
    Pair path_pair;
    Pair start = current;

    int i = current.first, j = current.second;
    cell_details[i][j].f = 0;
    cell_details[i][j].g = 0;
    cell_details[i][j].h = 0;
    cell_details[i][j].parent = { i, j };

    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> open_list;
    //Помещаем начальную ячейку в список open_list
    open_list.emplace(0, i, j);

    while (!open_list.empty()) {
        const Tuple& p = open_list.top();
        i = get<1>(p);
        j = get<2>(p);
        open_list.pop();
        closed_list[i][j] = true;

        draw(grid, path, end, row, col);
        Sleep(200);
        system("cls");

        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                Pair neighbour(i + x, j + y);

                if (is_valid(grid, neighbour, col, row)) {
                    if (check_win(neighbour, end)) {
                        cell_details[neighbour.first][neighbour.second].parent = { i, j };
                        path_making(cell_details, grid, start, end, col, row);
                        return;
                    }
                    else if (!closed_list[neighbour.first][neighbour.second] || cell_details[i][j].g + grid[neighbour.first][neighbour.second] < cell_details[neighbour.first][neighbour.second].g) {
                        double g_new, h_new, f_new;
                        g_new = cell_details[i][j].g + grid[neighbour.first][neighbour.second];
                        h_new = heuristic(neighbour, end);
                        f_new = g_new + h_new;

                        if (cell_details[neighbour.first][neighbour.second].f == -1 || cell_details[neighbour.first][neighbour.second].f > f_new) {
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

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    unsigned long int row, col, start_x, start_y, end_x, end_y, q;
    fin >> row >> col >> start_x >> start_y >> end_x >> end_y;

    Pair start(start_x, start_y);
    Pair end(end_x, end_y);

    vector< vector <int> > grid(row);

    for (int i = 0; i < row; ++i) {
        grid[i].resize(col);
        for (int j = 0; j < col; ++j) {
            fin >> q;
            grid[i][j] = q;
        }
    }
    a_star(grid, start, end, col, row);

}

