#include <iostream>
#include <cstring>
#define ID(rr, cc) (rr * c + cc)

using namespace std;

// declarations
const int S = 100, T = 101;
const int Inf = 1000000;
int r, c;
int G[102][102];
int cnt[102];
int total;
int cap[10200];
int to[10200];
int from[10200];
int rev[10200];
int cnt_x;
int xr[100], xc[100];

// build network
void edge_buff(int f, int t, int c, int re) {
    if (f < 0) {
        cout << f << endl; return;
    }
    cap[total] = c;
    to[total] = t;
    from[total] = f;
    G[f][cnt[f]++] = total;
    rev[total] = total+re;
    total++;
}

void add_edge(int f, int t, int c) {
    edge_buff(f, t, c, 1);
    edge_buff(t, f, c, -1);
}

void build_row(const int tr, const int tc) {
    for (int i = 0; i < c; i++)
        add_edge(ID(tr, i), ID(tr, tc), 1);
}

void build_col(const int tr, const int tc) {
    for (int i = 0; i < r; i++) {
        add_edge(ID(i, tc), ID(tr, tc), 1);
    }
}

void build_left_cross(const int tr, const int tc) {
    int i = tr, j = tc;
    while (i > 0 && j > 0) { i--; j--; }
    while (i < r && j < c) { add_edge(ID(i, j), ID(tr, tc), 1); i++; j++; }
}

void build_right_cross(const int tr, const int tc) {
    int i = tr, j = tc;
    while (i > 0 && j < c-1) { i--; j++; }
    while (i < r && j >= 0) { add_edge(ID(i, j), ID(tr, tc), 1); i++; j--; }
}

void build_mid() {
    for (int i = 0; i < cnt_x; i++) {
        int tr = xr[i], tc = xc[i];
        build_row(tr, tc);
        build_col(tr, tc);
        build_left_cross(tr, tc);
        build_right_cross(tr, tc);
    }
}

void init() {
    memset(G, -1, sizeof(G));
    memset(cnt, 0, sizeof(cnt));
    total = 0; cnt_x = 0;
}

int level[102];
#include <queue>

bool bfs() {
    memset(level, -1, sizeof(level)); level[S] = 0;
    queue<int> q; q.push(S);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int i = 0; i < cnt[cur]; i++) {
            int nxt = to[G[cur][i]];
            if (cap[G[cur][i]] > 0 && level[nxt] == -1) {
                level[nxt] = level[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return level[T] != -1;
}

int curarc[102];

int dfs(int cur, int flow) {
    if (cur == T || flow == 0) return flow;
    
    int vflow = 0;
    for (int &i = curarc[cur]; i < cnt[cur]; i++) {
        int nxt = to[G[cur][i]];
        int &cp = cap[G[cur][i]];
        if (level[nxt] != level[cur] + 1 || cp <= 0) continue;
        if (int f = dfs(nxt, min(cp, flow))) {
            cp -= f;
            vflow += f;
            cap[rev[G[cur][i]]] += f;
            flow -= f;
        }
    }
    
    return vflow;
}

int statis() {
    int res = 0;
    for (int i = 0; i < cnt[S]; i++)
        if (cap[G[S][i]] != Inf) res++;
        //cout << cap[G[S][i]] << ' '; cout << endl;
    return res;
}

void solve() {
    while (bfs()) {
        memset(curarc, 0, sizeof(curarc));
        cout << "one time!\n";
        dfs(S, Inf);
    }
    cout << statis() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    while (cin >> r >> c && r && c) {
        string in;
        init();
        for (int i = 0; i < r; i++) {
            cin >> in;
            for (int j = 0; j < (int)in.size(); j++) {
                char t = in[j];
                add_edge(S, ID(i, j), Inf);
                if (t == 'X') { add_edge(ID(i, j), T, 1); xr[cnt_x] = i; xc[cnt_x++] = j; }
            }
        }
        build_mid();
        solve();
    }
}
