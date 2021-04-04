#include "table.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void table::generate(int x,int y){
    srand(time(0));
    state = "started";
    if(diff == 9){
        mineamount = 10;
    }
    if(diff == 16){
        mineamount = 35;
    }
    if(diff == 24){
        mineamount = 91;
    }
    int cnt = 0;
    for(;;){
        int i = rand() % (diff * diff) + 1;
        int r = i / diff + 1;
        int c = i % diff;
        if(!c){
           c = diff;
           r--;
        }
        if(!mines[r][c] && (r != x || c != y)){ 
            mines[r][c] = 2;
            s[r][c] = 2;
            cnt++;
        }
        if(cnt == mineamount){
            break;
        }
    }
    for(int i = 1; i <= diff; i++){
        for(int j = 1; j <= diff; j++){
            if(mines[i][j - 1] == 2){
                values[i][j]++;
            }
            if(mines[i][j + 1] == 2){
                values[i][j]++;
            }
            if(mines[i - 1][j] == 2){
                values[i][j]++;
            }
            if(mines[i + 1][j] == 2){
                values[i][j]++;
            }
            if(mines[i - 1][j - 1] == 2){
                values[i][j]++;
            }
            if(mines[i - 1][j + 1] == 2){
                values[i][j]++;
            }
            if(mines[i + 1][j - 1] == 2){
                values[i][j]++;
            }
            if(mines[i + 1][j + 1] == 2){
                values[i][j]++;
            }
        }
    }
}
void table::flip(int x,int y){
    if(mines[x][y]){
        return ;
    }
    if(x > diff || y > diff || x < 1 || y < 1){
        return ;
    }
    mines[x][y] = 1;
    s[x][y] = 1;
    currentscore++;
    if(values[x][y] != 0){
        return ;
    }
    flip(x, y - 1);
    flip(x, y + 1);
    flip(x - 1, y);
    flip(x + 1, y);
    flip(x - 1, y - 1);
    flip(x - 1, y + 1);
    flip(x + 1, y - 1);
    flip(x + 1, y + 1);
}
void table::setnull(){
    check  = 0;
    for(int i = 1; i <= 25; i++){
        for(int j = 1; j <= 25; j++){
            s[i][j] = 0;
            values[i][j] = 0;
            mines[i][j] = 0;
        }
    }
}
void table::allflipped(){
    int ch = 1;
    for(int i = 1; i <= diff; i++){
        for(int j = 1; j <= diff; j++){
            if(!mines[i][j]){
                ch = 0;
                break;
            }
        }
    }
    check = ch;
    if(ch){
        for(int i = 1; i <= diff; i++){
            for(int j = 1; j <= diff; j++){
                if(mines[i][j] == 2){
                    s[i][j] = 4;
                }
            }
        }
    }
}
void table::printtable(int x,int y){
    if(!s[x][y] || s[x][y] == 2){
        cout<<"- ";
    }
    if(s[x][y] == 4){
        cout<<"X ";
    }
    if(s[x][y] == 1){
        cout<<values[x][y]<<" ";
    }
}