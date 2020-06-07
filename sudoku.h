#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>

using namespace std;
class Sudoku {
  public:
    Sudoku();
    Sudoku(int **init_map);
    int getElement(int r,int c) {
        return map[r][c];
    }

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    void check_and_fill(int total,vector<int>& row_ls,vector<int>& col_ls);
    int solve(int n,int total_n,vector<int>& row_ls,vector<int>& col_ls);
    int get_ept_num(vector<int>& row_v,vector<int>& col_v);
    vector<int> findNum(int x,int y);

    //volidate
    void setMap(int**set_map);
    void setElement(int x, int y,int v) {
        map[x][y]=v;
    }
    static const int sudokuRow = 9;
    static const int sudokuCol = 9;

  private:
    int map[sudokuRow][sudokuCol];
};
#endif

