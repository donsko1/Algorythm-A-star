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

//Структура для хранения данных о ячейке
struct cell {
    Pair parent;
    double f, g, h;
    cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
};

//Проверка ячейки на нахождении ее внутри массива
template <size_t ROW, size_t COLUMN>
bool is_valid(const array<array<int, COLUMN>, ROW>& grid, const Pair& point) {
    if (ROW > 0 && COLUMN > 0)
        return (point.first >= 0) && (point.first < ROW) && (point.second >= 0) && (point.second < COLUMN);
    return false;
}

//Проверка на достижение цели
bool check_win(const Pair& current, const Pair& end) {
    return current == end;
}

//Расчет эвристики h
int heuristic(const Pair& current, const Pair& end) {
    return sqrt((current.first - end.first) * (current.first - end.first) + (current.second - end.second) * (current.second - end.second));
}

template <size_t ROW, size_t COLUMN>
void draw(const array<array<int, COLUMN>, ROW>& grid, vector<Pair>path, const Pair& end) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {

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

//Отрисовка пути
template <size_t ROW, size_t COLUMN>
void path_making(const array<array<cell, COLUMN>, ROW>& cell_details, const array<array<int, COLUMN>, ROW>& grid, const Pair& end, const Pair& start) {
    stack<Pair> path;
    vector<Pair>path_pair;
    int g = 0;
    int row = end.first;
    int col = end.second;
    Pair next_node = cell_details[row][col].parent;
    ofstream fout("output.txt");

    do {
        path.push(next_node);
        path_pair.push_back(next_node);
        next_node = cell_details[row][col].parent;
        row = next_node.first;
        col = next_node.second;
    } while (cell_details[row][col].parent != next_node);

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {

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

    path.emplace(row, col);
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

template <size_t ROW, size_t COLUMN>
void a_star(const array<array<int, COLUMN>, ROW>& grid, const Pair& current, const Pair& end) {
    ofstream fout("output.txt");
    //Если начало не в диапазоне поля
    if (!is_valid(grid, current)) {
        cout << "Incorrect data";
        fout << "0";
        return;
    }

    //Если конец не в диапазоне поля
    if (!is_valid(grid, end)) {
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

    bool closed_list[ROW][COLUMN];
    memset(closed_list, false, sizeof(closed_list));

    array<array<cell, COLUMN>, ROW> cell_details;
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

        draw(grid, path, end);
        Sleep(100);
        system("cls");

        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                Pair neighbour(i + x, j + y);

                if (is_valid(grid, neighbour)) {
                    if (check_win(neighbour, end)) {
                        cell_details[neighbour.first][neighbour.second].parent = { i, j };
                        path_making(cell_details, grid, end, start);
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

int test(ifstream& fin, ifstream& fout, ifstream& res) {
    const int COLUMN = 10, ROW = 9;
    int start_x, start_y, end_x, end_y;
    string g, g_new;

    //Вводим координаты стартовой позиции и конечной точки
    fin >> start_y >> start_x >> end_y >> end_x;

    //Создаем пару стартовой и конечной точки
    Pair start(start_y, start_x);
    Pair end(end_y, end_x);

    //Создаем поле размером 9 столбцов на 10 строк
    array<array<int, COLUMN>, ROW> grid;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            fin >> grid[i][j];
        }
    }

    a_star(grid, start, end);
    cin.get();
    system("cls");

    fout >> g_new;
    res >> g;

    if (g == g_new)
        return 1;
    else
        return 0;

}

void tests() {
    int result = 0;
    {
        ifstream fin("tests\\1\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\1\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\2\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\2\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\3\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\3\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\4\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\4\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\5\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\5\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\6\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\6\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\7\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\7\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\8\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\8\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\9\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\9\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\10\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\10\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\11\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\11\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\12\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\12\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\13\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\13\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\14\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\14\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\15\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\15\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\16\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\16\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\17\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\17\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\18\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\18\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\19\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\19\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\20\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\20\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\21\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\21\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\22\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\22\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    {
        ifstream fin("tests\\23\\input.txt");
        ifstream fout("output.txt");
        ifstream res("tests\\23\\result.txt");
        result += test(fin, fout, res);
        fin.close();
        fout.close();
        res.close();
    }
    
    if (result == 23)
        cout << "OK";
    else
        cout << "WA";
}


int main()
{
    tests();
}
