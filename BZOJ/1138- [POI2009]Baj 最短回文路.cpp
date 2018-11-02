#include <bits/stdc++.h>

using namespace std;

const int N = 400+5;
const int M = 6e4+5;

struct Edge {
    Edge *next;
    int c, f, t;
    void *operator new (size_t, int f, int t, int c, Edge *next) {
        static Edge pool[M*4], *p = pool;
        Edge *e = p++;
        e->f = f; 
        e->t = t; 
        e->c = c; 
        e->next = next;
        return e;
    }
} *head[N] = {0x0}, *rev[26][N] = {0x0};

void addedge(Edge **egh, int f, int t, int c) {
    Edge *e = new (f, t, c, egh[f]) Edge;
    egh[f] = e;
}

struct Status {
    int f, t, c;
    void *operator new (size_t, int f, int t, int c) {
        static Status pool[N*N*54], *p = pool;
        Status *st = p++;
        st->f = f;
        st->t = t;
        st->c = c;
        return st;
    }
};

queue<Status*> q;

int n, m, u, v, x, y, d;
int f[N][N], g[N][N][26];
string c;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    for (int i = 1; i <= n; i++) {
        f[i][i] = 0;
        q.push(new (i, i, -1) Status);
    }
    for (int _ = 1; _ <= m; _++) {
        cin >> u >> v >> c;
        int chr = c[0]-'a';
        addedge(head, u, v, chr);
        addedge(rev[chr], v, u, chr);
        if (f[u][v] == -1) {
            f[u][v] = 1;
            q.push(new (u, v, -1) Status);
        }
    }
    while (!q.empty()) {
        Status *st = q.front();
        q.pop();
        if (st->c == -1) {
            for (Edge *e = head[st->t]; e != 0x0; e = e->next) {
                if (g[st->f][e->t][e->c] == -1) {
                    g[st->f][e->t][e->c] = f[st->f][st->t] + 1;
                    q.push(new (st->f, e->t, e->c) Status);
                }
            }
        } else {
            for (Edge *e = rev[st->c][st->f]; e != 0x0; e = e->next) {
                if (f[e->t][st->t] == -1) {
                    f[e->t][st->t] = g[st->f][st->t][st->c] + 1;
                    q.push(new (e->t, st->t, -1) Status);
                }
            }
        }
    }
    cin >> d;
    for (int i = 1; i <= d; i++) {
        cin >> y;
        if (i >= 2) {
            cout << f[x][y] << endl;
        }
        x = y;
    }
    return 0;
}