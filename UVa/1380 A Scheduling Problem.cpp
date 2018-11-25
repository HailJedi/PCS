#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>
#define maxn 205
#define INF 1000000000
using namespace std;

struct Edge {
    int u, v, d;
    Edge(int u = 0, int v = 0, int d = 0) : u(u), v(v), d(d) {}
};

vector<Edge> edges[maxn];

int root, n;
int have_father[maxn];

bool read() {
    n = 0;
    int a, b;
    string str; bool have_data = false;
    memset(have_father, 0, sizeof(have_father));
    for (int i = 0; i < maxn; i++) edges[i].clear();
    
    while (cin >> a && a) {
        if (a > n) n = a;
        have_data = true;
        while (cin >> str && str != "0") {
            int len = (int)str.length();
            char dir = str[len-1];
            if (dir == 'd' || dir == 'u') str = str.substr(0, len-1);
            stringstream ss(str);
            ss >> b;
            if (b > n) n = b;
            have_father[b] = 1;
            if (dir == 'd') {
                edges[a].push_back(Edge(a, b, 1));
                edges[b].push_back(Edge(b, a, 2));
            } else if (dir == 'u') {
                edges[a].push_back(Edge(a, b, 2));
                edges[b].push_back(Edge(b, a, 1));
            } else {
                edges[a].push_back(Edge(a, b, 0));
            }
        }
    }
    if (have_data) {
        for (int i = 1; i <= n; i++)
            if (!have_father[i] && !edges[i].empty())
                { root = i; break; }
    }
    return have_data;
}

int dfs(int u) {
    int res = 0;
    for (int i = 0; i < edges[u].size(); i++)
        if (edges[u][i].d == 1)
            res = max(res, dfs(edges[u][i].v)+1);
    return res;
}

struct UndirectedSon{
    int w, f, g;
    UndirectedSon(int w, int f, int g) : w(w), f(f), g(g) {}
};

bool cmp_f(const UndirectedSon &rhs1, const UndirectedSon &rhs2) {
    return rhs1.f < rhs2.f;
}

bool cmp_g(const UndirectedSon &rhs1, const UndirectedSon &rhs2) {
    return rhs1.g < rhs2.g;
}

int f[maxn], g[maxn];
int maxd;

bool dp(int u, int fa) {
    if (edges[u].empty()) {
        f[u] = g[u] = 0;
        return true;
    }
    
    int f0 = 0, g0 = 0;
    vector<UndirectedSon> sons;
    
    for (int i = 0; i < edges[u].size(); i++) {
        int w = edges[u][i].v;
        if (w == fa) continue;
        dp(w, u);
        int d = edges[u][i].d;
        if (d == 0) sons.push_back(UndirectedSon(w, f[w], g[w]));
        else if (d == 1) g0 = max(g0, g[w]+1);
        else f0 = max(f0, f[w]+1);
    }
    
    if (sons.empty()) {
        f[u] = f0; g[u] = g0;
        if (f[u] + g[u] > maxd) f[u] = g[u] = INF;
        return f[u] < INF;
    }
    
    f[u] = g[u] = INF;
    int s = (int)sons.size();
    
    sort(sons.begin(), sons.end(), cmp_f);
    int maxg[maxn];
    maxg[s-1] = sons[s-1].g;
    for (int i = s-2; i >= 0; i--)
        maxg[i] = max(maxg[i+1], sons[i].g);
    for (int p = 0; p <= s; p++) {
        int ff = f0, gg = g0;
        if (p > 0) ff = max(ff, sons[p-1].f+1);
        if (p < s) gg = max(gg, maxg[p]+1);
        if (ff + gg <= maxd) f[u] = min(f[u], ff);
    }
    
    sort(sons.begin(), sons.end(), cmp_g);
    int maxf[maxn];
    maxf[s-1] = sons[s-1].f;
    for (int i = s-2; i >= 0; i--)
        maxf[i] = max(maxf[i+1], sons[i].f);
    for (int p = 0; p <= s; p++) {
        int ff = f0, gg = g0;
        if (p > 0) gg = max(gg, sons[p-1].g+1);
        if (p < s) ff = max(ff, maxf[p]+1);
        if (ff + gg <= maxd) g[u] = min(g[u], gg);
    }
    
    return f[u] < INF;
}

int main() {
    while (read()) {
        maxd = 0;
        for (int i = 1; i <= n; i++) maxd = max(maxd, dfs(i));
        if (dp(root, -1)) cout << maxd+1 << endl;
        else cout << maxd+2 << endl;
    }
    return 0;
}
