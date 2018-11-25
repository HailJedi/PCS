
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

const int maxc = 10;
const int maxr = 5;
int id = 0;
int new_grid[maxc][maxr];
char grid[maxc][maxr];

bool init() {
    memset(new_grid, ' ', sizeof(new_grid));
    for(int i = 0; i < maxr; i++){
        string str;
        getline(cin, str);
        if (str[0] == '0') return false;
        for(int j = 0; j < maxc; j++) {
            new_grid[j][i] = str[j];
        }
    }
    return true;
}

int taken[3][3];
int X[6], Y[6];

bool are_same() {
    for (int r = 0; r < maxr; r++)
        for (int c = 0; c < maxc; c++)
            if (new_grid[c][r] != grid[c][r])
                return false;
    return true;
}

bool create(int till) {
    memset(grid, ' ', sizeof(grid));
    for(int id = 0; id <= till; id++) {
        int x = X[id]*2, y = Y[id];
        grid[x+1][y] = grid[x+3][y] = grid[x+1][y+2] = grid[x+3][y+2] = '_';
        grid[x][y+1] = grid[x][y+2] = grid[x+4][y+1] = grid[x+4][y+2] = '|';
        grid[x+1][y+1] = grid[x+2][y+1] = grid[x+3][y+1] = grid[x+2][y+2] = ' ';
    }
    for (int r = 0; r < maxr; r++) grid[9][r] = '#';
    return are_same();
}

bool draw(const int id){
    for(int x = 0; x <= 2; x++) {
        for(int y = 0; y <= 2; y++) if(!taken[x][y]) {
            taken[x][y] = 1;
            X[id] = x; Y[id] = y;
            if (create(id)) return true;
            if(id <= 4)
                if (draw(id+1)) return true;
            taken[x][y] = 0;
        }
    }
    return false;
}

void output_new_grid() {
    for (int r = 0; r < maxr; r++) {
        for (int c = 0; c < maxc; c++) {
            cout << new_grid[c][r];
        } cout << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    
    int kase = 0;
    while(init()) {
        memset(taken, 0, sizeof(taken));
        string ans = "Yes";
        if (!draw(0)) ans = "No";
        cout << "Case " << ++kase << ": " << ans << endl;
    }
    
    return 0;
}

