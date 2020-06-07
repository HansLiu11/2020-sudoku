#include <iostream>
#include <cstdlib>
#include "sudoku.h"

using namespace std;

int main() {
    int sudoku[Sudoku::sudokuCol][Sudoku::sudokuRow];
    Sudoku su;
    int *p[Sudoku::sudokuCol];
    int n,x,y;
    for(int i=0; i<Sudoku::sudokuCol; ++i) {
        p[i]=sudoku[i];
        for(int j=0; j<Sudoku::sudokuRow; ++j) {
            cin>>sudoku[i][j];
        }
    }
    su.setMap(p);
    while(cin>>n&&n!=0) {
        switch(n) {
        case 1:
            cin>>x>>y;
            su.swapNum(x,y);
            break;
        case 2:
            cin>>x>>y;
            su.swapRow(x,y);
            break;
        case 3:
            cin>>x>>y;
            su.swapCol(x,y);
            break;
        case 4:
            cin>>x;
            su.rotate(x);
            break;
        case 5:
            cin>>x;
            su.flip(x);
            break;
        }
    }
    for(int i=0; i<Sudoku::sudokuCol; ++i) {
        for(int j=0; j<Sudoku::sudokuRow; ++j) {
            cout<<su.getElement(i,j);
            if(j<8)
                cout<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

