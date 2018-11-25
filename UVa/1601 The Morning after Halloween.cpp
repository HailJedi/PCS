#include <iostream>
#include <cstdio>
#include <queue>
#include <cctype>
#include <cstring>
using namespace std;

const int maxw = 20;
const int maxs = maxw*maxw;

int dx[] = {-1, 0, 1, 0, 0};
int dy[] = {0, -1, 0, 1, 0};
int deg[maxs], G[maxs][5];
int s[3], t[3]; // departure and destination
int w, h, n;
char maze[maxw][maxw];

void init() {
    memset(maze, '0', sizeof(maze));
    memset(G, 0, sizeof(G));
    memset(s, 0, sizeof(s));
    memset(t, 0, sizeof(t));
}

void input() {
    for(int i = 0; i < h; i++)
        fgets(maze[i], 20, stdin);
    /*
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            cout << maze[i][j];
        cout << endl;
    } cout << endl;
    */
}

void build() {
    int id[maxw][maxw], cnt = 0, x[maxs], y[maxs];
    
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(maze[i][j] != '#') {
                id[i][j] = cnt; x[cnt] = i; y[cnt] = j;
                char ch = maze[i][j];
                if(islower(ch)) s[ch-'a'] = cnt;
                else if(isupper(ch)) t[ch-'A'] = cnt;
                cnt++;
            }
        }
    }
    
    for(int i = 0; i < cnt; i++) {
        deg[i] = 0;
        for(int j = 0; j <= 4; j++) {
            int nx = x[i] + dx[j], ny = y[i] + dy[j];
            if(maze[nx][ny] != '#') {
                G[i][deg[i]++] = id[nx][ny];
            }
        }
    }
    
    if(n <= 2) { deg[cnt] = 1; G[cnt][0] = cnt; s[2] = t[2] = cnt++; }
    if(n <= 1) { deg[cnt] = 1; G[cnt][0] = cnt; s[1] = t[1] = cnt++; }
}

bool isCrossing(int a, int a1, int b, int b1) {
    return a1 == b1 || (b == a1 && a == b1);
}

int ID(int a, int b, int c) {
    return (a<<16)|(b<<8)|c;
}

int dist[maxs][maxs][maxs];
int solve() {
    queue<int> Q;
    memset(dist, -1, sizeof(dist));
    
    int a = s[0], b = s[1], c = s[2];
    Q.push(ID(a, b, c)); dist[a][b][c] = 0;
    
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        int a = (u>>16)&0xff, b = (u>>8)&0xff, c = u&0xff;
        
        if(a == t[0] && b == t[1] && c == t[2]) return dist[a][b][c];
        
        for(int i = 0; i < deg[a]; i++) {
            int a1 = G[a][i];
            
            for(int j = 0; j < deg[b]; j++) {
                int b1 = G[b][j];
                if(isCrossing(a, a1, b, b1)) continue;
                
                for(int k = 0; k < deg[c]; k++) {
                    int c1 = G[c][k];
                    if(isCrossing(a, a1, c, c1) || isCrossing(b, b1, c, c1)) continue;
                    if(dist[a1][b1][c1] != -1) continue;
                    
                    dist[a1][b1][c1] = dist[a][b][c] + 1;
                    Q.push(ID(a1, b1, c1));
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    
    while(scanf("%d%d%d\n", &w, &h, &n) && n) {
        init();
        input();
        build();
        cout << solve() << endl;
    }
    
    return 0;
}
