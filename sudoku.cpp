#include "sudoku.h"
#include <vector>
#include <cstdlib>
using namespace std;

Sudoku::Sudoku() {
    for(int i=0; i<sudokuCol; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            map[i][j]=0;
        }
    }
}
Sudoku::Sudoku(int **init_map) {
    for(int i=0; i<sudokuCol; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            map[i][j]= init_map[i][j];
        }
    }
}

// transform
void Sudoku::swapNum(int x, int y) {
    for(int i=0; i<sudokuCol; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            if(map[i][j]==x)
                map[i][j]=y;
            else if(map[i][j]==y)
                map[i][j]=x;
        }
    }
}

void Sudoku::swapRow(int x, int y) {
    int t;
    for(int i=0; i<3; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            t= map[x*3+i][j];
            map[3*x+i][j]=map[3*y+i][j];
            map[3*y+i][j]=t;
        }
    }
}

void Sudoku::swapCol(int x, int y) {
    int t;
    for(int i=0; i<sudokuCol; ++i) {
        for(int j=0; j<3; ++j) {
            t= map[i][x*3+j];
            map[i][x*3+j]=map[i][y*3+j];
            map[i][y*3+j]=t;
        }
    }

}

void Sudoku::rotate(int x) {
    int t;
    for(int n=0; n<x%4; ++n) {
        for(int i=0 ; i<sudokuRow/2; ++i) {
            for(int j=i; j<sudokuRow-i-1; ++j) {
                t=map[i][j];
                map[i][j]=map[sudokuRow-j-1][i];
                map[sudokuRow-j-1][i]=map[sudokuRow-i-1][sudokuRow-j-1];
                map[sudokuRow-i-1][sudokuRow-j-1]=map[j][sudokuRow-i-1];
                map[j][sudokuRow-i-1]=t;
            }
        }
    }
}
void Sudoku::flip(int x) {
    int t;
    if(x==0) {
        for(int i=0; i<sudokuCol/2; ++i) {
            for(int j=0; j<sudokuRow; ++j) {
                t= map[i][j];
                map[i][j]=map[sudokuCol-i-1][j];
                map[sudokuCol-i-1][j]=t;
            }
        }
    } else {
        for(int i=0; i<sudokuCol; ++i) {
            for(int j=0; j<sudokuRow/2; ++j) {
                t= map[i][j];
                map[i][j]=map[i][sudokuRow-j-1];
                map[i][sudokuRow-j-1]=t;
            }
        }

    }
}
// solve
void Sudoku::check_and_fill(int total,vector<int>& row_ls,vector<int>& col_ls) {
    vector<int> cdd;
    int row,col;
    int  ck[9]= {0},cp[9]= {0};
    vector<int> cd[total];

    for(int i=0; i<total; ++i) {
        col = col_ls.at(i);
        row = row_ls.at(i);
        cd[i] = findNum(col,row);
    }
    for(int i=0; i<total; ++i) {
        for(int k=0; k<9; ++k) {
            ck[k]= 0;
            cp[k]= 0;
        }
        col = col_ls.at(i);
        row = row_ls.at(i);
        for(int k=0; k<cd[i].size(); ++k)
            ck[cd[i].at(k)-1]= 1;
        for(int j=0; j<total; ++j) {
            if(col == col_ls.at(j) && i!=j) { //same col
                for(int k=0; k<cd[j].size(); ++k)
                    cp[cd[j].at(k)-1]= 1;
            }
        }
        cdd.clear();
        for(int k=0; k<9; ++k) {
            if(ck[k]==1 && cp[k]==0)
                cdd.push_back(k+1);
            cp[k] = 0;
        }
        if(cdd.size()==1)
            map[col][row] = cdd.at(0);
        else {
            for(int j=0; j<total; ++j) {
                if(row ==row_ls.at(j) && i!=j) { //same row
                    for(int k=0; k<cd[j].size(); ++k)
                        cp[cd[j].at(k)-1]= 1;
                }
            }
            cdd.clear();
            for(int k=0; k<9; ++k) {
                if(ck[k]== 1 && cp[k]== 0)
                    cdd.push_back(k+1);
                cp[k]=0;
            }
            if(cdd.size()==1)
                map[col][row] = cdd.at(0);
            else {
                for(int j=0; j<total; ++j) {
                    if(row/3==row_ls.at(j)/3 && col/3==col_ls.at(j)/3 && i!=j) { //same cell
                        for(int k=0; k<cd[j].size(); ++k)
                            cp[cd[j].at(k)-1]= 1;
                    }
                }
                cdd.clear();
                for(int k=0; k<9; ++k) {
                    if(ck[k]==1 && cp[k]== 0)
                        cdd.push_back(k+1);
                }
                if(cdd.size()==1) {
                    map[col][row] = cdd.at(0);
                }
            }
        }
    }
}
int Sudoku::solve(int n,int total_n,vector<int>& row_ls,vector<int>& col_ls) {
    if(n==total_n)
        return 1;
    vector<int> candidate;
    int row,col,res;
    row = row_ls.at(n);
    col = col_ls.at(n);
    candidate = findNum(col,row);
    if(candidate.size()==0)
        return 0;
    for(int i=0; i<candidate.size(); ++i) {
        int value=candidate.at(i);

        map[col][row]=value;
        res = solve(n+1,total_n,row_ls,col_ls);
        if(res==0)
            map[col][row]=0;
        else
            return res;

    }
    return res;
}
int Sudoku::get_ept_num(vector<int>& row_v,vector<int>& col_v) {
    int count;
    for(int i=0; i<sudokuCol; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            if(map[i][j]==0) {
                row_v.push_back(j);
                col_v.push_back(i);
                count++;
            }
        }
    }
    return count;
}
vector<int> Sudoku::findNum(int x,int y) {
    int row_ck[9]= {0},col_ck[9]= {0};
    int cell_ck[9]= {0};
    vector<int> result_num;
    for(int i=0; i<9; i++) { //row column
        if(map[x][i]!=0)
            ++row_ck[map[x][i]-1];
        if(map[i][y]!=0)
            ++col_ck[map[i][y]-1];
    }
    for(int i=0; i<3; i++) { //cell
        for(int j=0; j<3; j++) {
            if(map[(x/3)*3+i][(y/3)*3+j]!=0)
                ++cell_ck[map[(x/3)*3+i][(y/3)*3+j]-1];
        }
    }
    for(int k=0; k<9; k++) {
        if(row_ck[k]==0 && col_ck[k]==0 && cell_ck[k]==0)
            result_num.push_back(k+1);
    }
    return result_num;
}
void Sudoku::setMap(int **set_map) {
    for(int i=0; i<sudokuCol ; ++i) {
        for(int j=0; j<sudokuRow; ++j) {
            map[i][j]= set_map[i][j];
        }
    }
}

