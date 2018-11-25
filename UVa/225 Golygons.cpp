#include<iostream>
#include<set>
#include<cstring>
#include<cmath>
#include<map>
using namespace std;

const int buf = 105;
const int maxn = 3*buf;
int blocks[maxn][maxn];
int path[maxn];
int lastLenth;
int total, S[maxn];

const char directions[] = {'e', 'n', 's', 'w'};
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
const int startX = 0;
const int startY = 0;


void init() {
    S[0] = 0;
    for(int i = 1; i <= 20; i++) S[i] = S[i-1] + i;
}

void output() {
    for(int i = 0; i < lastLenth; i++) {
        cout << directions[path[i]];
    } cout << endl;
}

bool block_in_the_way(int sx, int sy, int tx, int ty) {
    if(sx > tx) swap(sx, tx);
    if(sy > ty) swap(sy, ty);
    for(int x = sx; x <= tx; x++) {
        for(int y = sy; y <= ty; y++) {
            if(blocks[x+buf][y+buf]) return true;
        }
    }
    return false;
}

bool is_time_to_go_back(int curDepth, int curX, int curY) {
    int manhattan_dist = abs(curX) + abs(curY);
    int remain_dist = S[lastLenth] - S[curDepth];
    if(remain_dist < manhattan_dist) return true;
    return false;
}

int vis[maxn][maxn];

void dfs(int curDepth, int curX, int curY, int lastDir) {
    if(curDepth == lastLenth) {
        if(curX == startX && curY == startY) {
            output();
            total++;
        }
        return;
    }
    
    if(is_time_to_go_back(curDepth, curX, curY)) return;
    
    for(int dir = 0; dir <= 3; dir++) {
        int newX = curX + dx[dir]*(curDepth+1);
        int newY = curY + dy[dir]*(curDepth+1);
        
        if(dir + lastDir == 3 || dir == lastDir) continue;
        if(abs(newX) > buf || abs(newY) > buf) continue;
        if(block_in_the_way(curX, curY, newX, newY)) continue;
        if(vis[newX+buf][newY+buf]) continue;
        
        vis[newX+buf][newY+buf] = 1;
        path[curDepth] = dir;
        dfs(curDepth+1, newX, newY, dir);
        vis[newX+buf][newY+buf] = 0;
    }
}

void solve() {
    total = 0;
    
    dfs(0, startX, startY, -1);
    
    cout << "Found "  << total << " golygon(s)." << endl << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    init();
    
    int T; cin >> T;
    
    int n, x, y;
    while (T--) {
        cin >> lastLenth;
        cin >> n;
        memset(blocks, 0, sizeof(blocks));
        for (int i = 1; i <= n; i++) {
            cin >> x >> y;
            if(abs(x) > buf || abs(y) > buf) continue;
            blocks[x+buf][y+buf] = 1;
        }
        solve();
    }
    return 0;
}

