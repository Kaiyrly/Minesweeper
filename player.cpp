#include "player.h"
#include <string>
#include <iostream>
#include <utility>
#include "table.h"
#include <sstream>

using namespace std;

pair<int, int> player::enterNums(table t){
    int ch = 1;
    cout.flush();
    string n;
    getline(cin, n);
    string q[5];
    q[0] = "";
    q[1] = "";
    int j = 0;
    for(int i = 0; i < n.size(); i++){
        if(j > 1){
            break;
        }
        if(n[i] == ' '){
            if(q[j].size() == 0){
                continue;
            }  
            j++;
            continue;
        }
        if(n[i] >= '0' && n[i] <= '9'){      
            q[j] += n[i];
            continue;
        }
        else{
            ch = 0;
            break;
        }    
    }
    if(q[0].size() == 0 || q[1].size() == 0 || j < 1){
        ch = 0;
    }
    stringstream x2(q[0]), y2(q[1]);
    x2 >> x;
    y2 >> y;
    if(!n.size()){
        return enterNums(t);
    }
    if(!ch){
        cout<<"Invalid move. Try again: ";
        return enterNums(t);
    }
    if(x > t.diff || y > t.diff || x < 1 || y < 1){
        cout<<"Invalid move. Try again: ";
        return enterNums(t);
    }
    else if(t.mines[x][y] == 1){
        cout<<"Invalid move. Try again: ";
        return enterNums(t);
    }
    else{
        return make_pair(x, y);
    }
}