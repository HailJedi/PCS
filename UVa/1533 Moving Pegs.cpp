#include <iostream>
#include <set>
#include <queue>
#define FOR_ELEM(elem, seq) for(set<int>::const_iterator elem = seq.begin(); elem != seq.end(); ++elem)
//#define local
using namespace std;

const bool is_linked[15][15] = {
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0},
    {1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1},
    {0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1},
    {0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0}
};

const int direct[15][6] = {
    {-1, -1, -1, -1, 2, 3}, {-1, 1, -1, 3, 4, 5}, {1, -1, 2, -1, 5, 6},
    {-1, 2, -1, 5, 7, 8}, {2, 3, 4, 6, 8, 9}, {3, -1, 5, -1, 9, 10},
    {-1, 4, -1, 8, 11, 12}, {4, 5, 7, 9, 12, 13}, {5, 6, 8, 10, 13, 14},
    {6, -1, 9, -1, 14, 15}, {-1, 7, -1, 12, -1, -1}, {7, 8, 11, 13, -1, -1},
    {8, 9, 12, 14, -1, -1}, {9, 10, 13, 15, -1, -1}, {10, -1, 14, -1, -1, -1}
};

const int max_scale = (1<<15);
set<int> blanks[max_scale];
set<int> pegs[max_scale];
set<int> used;
queue<int> que;
int head_hsh;
int empty;
int pth_1[max_scale];
int pth_2[max_scale];
int last[max_scale];

void solve() {
    que.push(head_hsh);
    
    while (!que.empty()) {
        int cur = que.front(); que.pop();
        
        if (pegs[cur].size() == 1 && pegs[0].count(empty)) {
            return;
        }
        
        FOR_ELEM(pg, pegs[cur]) {
            for (int dir = 0; dir <= 5; dir++) {
                
                int cpy_hsh = cur;
                set<int> cpy_blk = blanks[cur];
                set<int> cpy_pgs = pegs[cur];
                int cpy_pg = *pg;
                
                while (cpy_pg != -1) {
                    if (cpy_blk.count(cpy_pg)) {
                        que.push(cpy_hsh);
                        blanks[cpy_hsh] = cpy_blk;
                        pegs[cpy_hsh] = cpy_pgs;
                        pth_1[cpy_hsh] = *pg;
                        pth_2[cpy_hsh] = cpy_pg;
                        last[cpy_hsh] = cur;
                    }
                    
                    cpy_pgs.erase(cpy_pg);
                    cpy_blk.insert(cpy_pg);
                    cpy_hsh &= ~(1<<cpy_pg);
                    
                    cpy_pg = direct[cpy_pg][dir];
                }
            }
        }
        
    }
}

void init(int hd) {
    head_hsh = ~(1<<hd);
    for (int i = 0; i < 15; i++)
        if (i == hd)
            blanks[head_hsh].insert(i);
        else pegs[head_hsh].insert(i);
}

void clear() {
    FOR_ELEM(elem, used) {
        blanks[*elem].clear();
        pegs[*elem].clear();
    }
    used.clear();
}

int main() {
    ios::sync_with_stdio(false);
#ifdef local
    freopen("result.txt", "w", stdout);
#endif
    
    int T; cin >> T;
    while (T--) {
        clear();
        cin >> empty; empty--;
        init(empty);
        solve();
    }
    return 0;
}
