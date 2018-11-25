#include <iostream>
#include <set>
#define maxn 10
using namespace std;

// data structures
struct Cell {
    int x, y;
    Cell(int x, int y) : x(x), y(y) {}
    bool operator < (const Cell &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};
typedef set<Cell> Polyomino;
set<Polyomino> Polyomino_Group[maxn+1];
#define FOR_POLY(p, g) for(set<Polyomino>::const_iterator p = (g).begin(); p != (g).end(); ++p)
#define FOR_CELL(c, p) for(Polyomino::const_iterator c = (p).begin(); c != (p).end(); ++c)

// normalize
Polyomino normalize(Polyomino &p0) {
    Polyomino p = p0;
    int min_x = p.begin()->x, min_y = p.begin()->y;
    FOR_CELL(c, p) {
        min_x = min(min_x, c->x);
        min_y = min(min_y, c->y);
    }
    Polyomino p2;
    FOR_CELL(c, p) {
        p2.insert(Cell(c->x - min_x, c->y - min_y));
    }
    return p2;
}

// rotate
Polyomino rotate(Polyomino &p0) {
    Polyomino p2;
    FOR_CELL(c, p0) {
        p2.insert(Cell(c->y, -c->x));
    }
    return normalize(p2);
}

// flip
Polyomino flip(Polyomino &p0) {
    Polyomino p2;
    FOR_CELL(c, p0) {
        p2.insert(Cell(-c->x, c->y));
    }
    return normalize(p2);
}

// try to insert new square in current instance polyomino
void try_insert(const Cell &new_cell, const Polyomino &p0) {
    
    // insert first
    // normalize target instance polyomino
    Polyomino p = p0;
    p.insert(new_cell);
    p = normalize(p);
    
    // rotate four times
    // search if rotated instance is in instance size's polyominos
    //        then return
    int size = (int)p.size();
    for (int i = 1; i <= 4; i++) {
        if (Polyomino_Group[size].count(p) != 0) return;
        p = rotate(p);
    }
    
    // flip instance
    p = flip(p);
    
    // rotate again
    for (int i = 1; i <= 4; i++) {
        if (Polyomino_Group[size].count(p) != 0) return;
        p = rotate(p);
    }
    
    Polyomino_Group[size].insert(p);
    // finally insert new polyomino into group
}

int ans[maxn+1][maxn+1][maxn+1];

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

// main algorithm
void generate() {
    
    // generate
    
    // for size from 2 to 10
    //     for instance polyomino with size-1
    //         for every squares in instance polyomino
    //             go to four directions
    //             if new position is not in current instance polyomino
    //             then try to insert new square in current instance polyomino
    
    Polyomino s; s.insert(Cell(0, 0));
    Polyomino_Group[1].insert(s);
    
    for (int size = 2; size <= 10; size++) {
        FOR_POLY(p, Polyomino_Group[size-1]) {
            FOR_CELL(c, *p) {
                for (int i = 0; i <= 3; i++) {
                    Cell new_cell(c->x + dx[i], c->y + dy[i]);
                    if (p->count(new_cell) == 0) try_insert(new_cell, *p);
                }
            }
        }
    }
    
    // for size from 1 to 10
    //     for w from 1 to 10
    //         for h from 1 to 10
    //             for every instance polyomino in polyominos of size
    //                 find upper_bound x and y
    //                 if in bound
    //                 then ans[size][w][h] + 1
    
    
    for (int size = 1; size <= 10; size++) {
        for (int w = 1; w <= 10; w++) {
            for (int h = 1; h <= 10; h++) {
                FOR_POLY(p, Polyomino_Group[size]) {
                    int max_x = 0, max_y = 0;
                    FOR_CELL(c, *p) {
                        max_x = max(max_x, c->x);
                        max_y = max(max_y, c->y);
                    }
                    if(min(max_x, max_y) < min(w, h) && max(max_x, max_y) < max(w, h))
                        ans[size][w][h] += 1;
                }
            }
        }
    }
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    generate();
    int n, w, h;
    while(cin >> n >> w >> h) {
        cout << ans[n][w][h] << endl;
    }
    return 0;
}

