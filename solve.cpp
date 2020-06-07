#include <iostream>
#include <cstdlib>
#include "sudoku.h"

using namespace std;

int main() {
    int sudoku[Sudoku::sudokuCol][Sudoku::sudokuRow];
    Sudoku su;
    int *p[Sudoku::sudokuCol];
    int bk_n,res=0;
    vector<int> empty_row,empty_col;

    for(int i=0; i<Sudoku::sudokuCol; ++i) {
        p[i]=sudoku[i];
        for(int j=0; j<Sudoku::sudokuRow; ++j) {
            cin>>sudoku[i][j];
        }
    }
    su.setMap(p);
    bk_n = su.get_ept_num(empty_row,empty_col);
    if(9*9-bk_n <17) {
        cout<< 2 << "\n";
        return 0;
    }
    su.check_and_fill(bk_n,empty_row,empty_col);
    empty_row.clear();
    empty_col.clear();
    bk_n = su.get_ept_num(empty_row,empty_col);
    res = su.solve(0,bk_n,empty_row,empty_col);
    cout<<res<<"\n";
    if(res==1) {
        for(int i=0; i<Sudoku::sudokuCol; ++i) {
            for(int j=0; j<Sudoku::sudokuRow; ++j) {
                cout<<su.getElement(i,j);
                if(j<8)
                    cout<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}

