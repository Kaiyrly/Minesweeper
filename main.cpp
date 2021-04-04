#include <iostream>
#include "table.h"
#include "player.h"
using namespace std;
table t;
player p[5];
void game(){
    if(t.state == "finished"){
        t.setnull();
        p[0].score = 0;
        p[1].score = 0;
        cout<<"Enter first player's name: ";
        cout.flush();
        cin>>p[0].name;
        cout<<"Enter second player's name: ";
        cout.flush();
        cin>>p[1].name;
        t.turn = 0;
        cout<<"Choose the difficulty [easy/medium/hard]:";
        string s2;
        while(s2 != "easy" && s2 != "medium" && s2 != "hard"){
            cout.flush();
            cin>>s2;
            if(s2 != "easy" && s2 != "medium" && s2 != "hard"){
                cout<<"Invalid input. Try again:";
            }
        }
        t.level = s2;
        if(t.level == "easy"){
            t.diff = 9;
        }
        if(t.level == "medium"){
            t.diff = 16;
        }
        if(t.level == "hard"){
            t.diff = 24;
        }
        for(int i = 1; i <= t.diff; i++){
            for(int j = 1; j <= t.diff; j++){
                t.printtable(i, j);
            }
            cout<<"\n";
        }
        cout<<p[0].name<<"'s score: "<<p[0].score<<"\n";
        cout<<p[1].name<<"'s score: "<<p[1].score<<"\n";
        cout<<"It's "<<p[t.turn].name<<"'s turn.\n";
        cout<<"Enter your move (row [1-"<<t.diff<<"] column[1-"<<t.diff<<"]:";
        pair<int, int> z = p[t.turn].enterNums(t);
        int x, y;
        x = z.first;
        y = z.second;
        t.generate(x, y);
        t.currentscore = 0;
        t.flip(x, y);
        p[t.turn].score += t.currentscore;
        game();
    }
    else{
        for(int i = 1; i <= t.diff; i++){
            for(int  j = 1; j <= t.diff; j++){
                t.printtable(i, j);
            }
            cout<<'\n';
        }
        if(t.state == "lose"){
            cout<<"Oops! "<<p[t.turn].name<<" lose. Would you like to play again?(Y/N): ";
            string c;
            while(c != "Y" && c != "N"){
                cout.flush();
                cin>>c;
                if(c != "Y" && c != "N"){
                    cout<<"Invalid input. Try again: ";
                }
            }
            if(c == "Y"){
                t.state = "finished";
                game();
            }
            else{
                exit(0);
            }
        }
        t.turn = (t.turn + 1) % 2;
        cout<<p[0].name<<"'s score: "<<p[0].score<<"\n";
        cout<<p[1].name<<"'s score: "<<p[1].score<<"\n";
        cout<<"It's "<<p[t.turn].name<<"'s turn.\n";
        if(!p[t.turn].score){
            cout<<"Enter your move (row [1-"<<t.diff<<"] column[1-"<<t.diff<<"]:";
        }
        else cout<<"Enter your next move (row [1-"<<t.diff<<"] column[1-"<<t.diff<<"]:";
        pair<int, int> z = p[t.turn].enterNums(t);
        int x, y;
        x = z.first;
        y = z.second;
        if(!t.mines[x][y]){
            t.currentscore = 0;
            t.flip(x, y);
            p[t.turn].score += t.currentscore;
            t.allflipped();
            if(t.check){
                for(int i = 1; i <= t.diff; i++){
                    for(int j = 1; j <= t.diff; j++){
                        t.printtable(i, j);
                    }
                    cout<<'\n';
                }
                cout<<p[0].name<<"'s score: "<<p[0].score<<"\n";
                cout<<p[1].name<<"'s score: "<<p[1].score<<"\n";
                if(p[0].score > p[1].score){
                    cout<<p[0].name<<" win. Congrats!\n";
                }
                else if(p[0].score < p[1].score){
                    cout<<p[1].name<<" win. Congrats!\n";
                }
                else{
                    cout<<"Tie!\n";
                }
                t.state = "finished";
                cout<<"Would you like to play again?(Y/N): ";
                string c;
                while(c != "Y" && c != "N"){
                    cout.flush();
                    cin>>c;
                    if(c != "Y" && c != "N"){
                        cout<<"Invalid input. Try again: ";
                    }
                }   
                if(c == "Y"){
                    t.state = "finished";
                    game();
                }
                else{
                    exit(0);
                }
            }
            game();
        }
        if(t.mines[x][y] == 2){
            for(int i = 1; i <= t.diff; i++){
                for(int j = 1; j<= t.diff; j++){
                    if(t.mines[i][j] == 2){
                        t.s[i][j] = 4;
                    }
                }
            }
            t.state = "lose";
            game();
        }
    }
}
int main() {
    game();
}