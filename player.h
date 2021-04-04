#include <string>
#include "table.h"

class player{
    public:
        int score, x, y;
        std::string name;
        std::pair<int, int> enterNums(table t);
};