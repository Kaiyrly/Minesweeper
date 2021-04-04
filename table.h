#include <string>
#ifndef TABLE_H
#define TABLE_H
class table{
    public:
        int check = 0, turn, diff, mineamount, mines[30][30], values[30][30], s[30][30], currentscore;
        std::string state = "finished", level;
        void generate(int x,int y);
        void flip(int x,int y);
        void setnull();
        void allflipped();
        void printtable(int x,int y);
};   
#endif