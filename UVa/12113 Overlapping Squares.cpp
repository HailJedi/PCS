#include <iostream>
#include <cstring>
#include <string>
#include <set>
using namespace std;

const int maxc = 10;
const int maxr = 5;
unsigned long long Inf = 9223372036854775807;

struct Grid {
    char grid[maxc][maxr];
    unsigned long long identity;
    bool operator < (const Grid &rhs) const {
        return this->identity < rhs.identity;
    }
    void get_identity() {
        this->identity = 0;
        for (int r = 0; r < maxr; r++) {
            for (int c = 0; c < maxc; c++) {
                int id = r * maxc + c;
                char ch = grid[c][r];
                if (ch != ' ' && ch != '|' && ch != '_' && ch != '#') { this->identity = Inf++; return; }
                if (ch == '|' && c % 2 == 1) { this->identity = Inf++; return; }
                if (ch == '_' && c % 2 == 0) { this->identity = Inf++; return; }
                if (ch == '#' && c != 9) { this->identity = Inf++; return; }
                if (ch != ' ') this->identity |= (1<<id);
            }
        }
    }
};
set<Grid> valid_grids;
Grid new_grid = Grid();

bool init() {
    char grid[maxc][maxr]; memset(grid, ' ', sizeof(grid));
    for(int i = 0; i < maxr; i++){
        string str;
        getline(cin, str);
        if (str[0] == '0') return false;
        for(int j = 0; j < maxc; j++) {
            grid[j][i] = str[j];
        }
    }
    memcpy(new_grid.grid, grid, sizeof(grid));
    new_grid.get_identity();
    
    return true;
}

int taken[3][3];
int X[6], Y[6];

void create(int till) {
    char grid[maxc][maxr];
    memset(grid, ' ', sizeof(grid));
    for(int id = 0; id <= till; id++) {
        int x = X[id]*2, y = Y[id];
        grid[x+1][y] = grid[x+3][y] = grid[x+1][y+2] = grid[x+3][y+2] = '_';
        grid[x][y+1] = grid[x][y+2] = grid[x+4][y+1] = grid[x+4][y+2] = '|';
        grid[x+1][y+1] = grid[x+2][y+1] = grid[x+3][y+1] = grid[x+2][y+2] = ' ';
    }
    for (int r = 0; r < maxr; r++) grid[9][r] = '#';
    Grid a_new_grid = Grid();
    memcpy(a_new_grid.grid, grid, sizeof(grid));
    a_new_grid.get_identity();
    valid_grids.insert(a_new_grid);
}

void draw(const int id){
    for(int x = 0; x <= 2; x++) {
        for(int y = 0; y <= 2; y++) if(!taken[x][y]) {
            taken[x][y] = 1;
            X[id] = x; Y[id] = y;
            create(id);
            if(id <= 4) draw(id+1);
            taken[x][y] = 0;
        }
    }
}

int main()
{
    memset(taken, 0, sizeof(taken));
    valid_grids.clear();
    draw(0);
    
    long long kase = 0;
    while(init()) {
        string ans = "Yes";
        if (!valid_grids.count(new_grid) || new_grid.identity == Inf) ans = "No";
        printf("Case %lld: %s\n", ++kase, ans.c_str());
    }
    
    return 0;
}




