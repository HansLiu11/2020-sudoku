#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sudoku.h"

using namespace std;

int main() {
    int sudoku[Sudoku::sudokuCol][Sudoku::sudokuRow]= {
        0,0,0,0,0,0,1,0,0,
        9,6,7,0,0,0,0,0,0,
        0,0,0,0,5,0,0,0,7,
        0,4,0,2,8,0,5,0,0,
        0,0,8,0,0,0,0,0,1,
        0,0,0,0,0,1,2,7,0,
        0,0,3,5,2,0,0,0,0,
        8,0,0,0,3,0,0,9,2,
        1,0,0,0,7,0,4,0,0
    };
    Sudoku su;
    int *p[Sudoku::sudokuCol];
    int n,x,y,count;
    srand(time(NULL));
    for(int i=0; i<Sudoku::sudokuCol; ++i) {
        p[i]=sudoku[i];
    }
    su.setMap(p);
    count = rand()%5+1;
    while(count!=0) {
        n = rand()%4+1;
        x = rand()%3;
        y = rand()%3;
        switch(n) {
        case 1:
            su.swapRow(x,y);
            break;
        case 2:
            su.swapCol(x,y);
            break;
        case 3:
            su.rotate(x);
            break;
        case 4:
            su.flip(x);
            break;
        }
        count--;
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


