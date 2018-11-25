#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cstdio>
#define X(x) (x)
#define Y(x) (x+V)
using namespace std;

int V, E, sink, source;

struct Edge {
    int from, to, cap, rev, cost;
};

const int maxn = 200 + 10;
const int INF = 0x3f3f3f3f;
vector<Edge> edges;
vector<int> G[maxn];

void addEdge(int from, int to, int cap, int cost) {
    int idx = edges.size();
    G[from].push_back(idx);
    G[to].push_back(idx+1);
    edges.push_back((Edge){from, to, cap, idx+1, cost});
    edges.push_back((Edge){to, from, 0, idx, -cost});
}

void init() {
    edges.clear();
    source = 0; sink = 2*V+1;
    for(int v = source; v <= sink; v++) G[v].clear();
    
    for (int i = 1; i <= V; i++) {
        addEdge(source, X(i), 1, 0);
        addEdge(Y(i), sink, 1, 0);
    }

    int v, c;
    for(int u = 1; u <= V; u++) {
        while (true) {
            cin >> v;
            if (!v) break;
            cin >> c;
            addEdge(X(u), Y(v), 1, c);
        }
    }
}

int cost[maxn];
int vis[maxn];
int curFlow[maxn];
int pre[maxn];

bool BelFord(int &minCost, int &maxFlow) {
    for(int i = source; i <= sink; i++) {
        cost[i] = INF;
        vis[i] = 0;
    }
    vis[source] = 1; pre[source] = -1;
    cost[source] = 0; curFlow[source] = INF;
    queue<int> que;
    que.push(source); 
    while(!que.empty()) {
        int u = que.front(); que.pop();
        vis[u] = 0; 
        for(int i = 0; i < G[u].size(); i++) {
            Edge &e = edges[G[u][i]];
            if(e.cap > 0 && cost[e.to] > cost[u] + e.cost) {
                cost[e.to] = cost[u] + e.cost;
                pre[e.to] = G[u][i];
                curFlow[e.to] = min(curFlow[u], e.cap);
                if(!vis[e.to]) {
                    que.push(e.to);
                    vis[e.to] = 1;
                }
            }
        }
    }
    if(cost[sink] == INF) return false;
    
    minCost += curFlow[sink] * cost[sink];
    maxFlow += curFlow[sink];
    
    int u = sink;
    while(u != source) {
        Edge &e = edges[pre[u]];
        e.cap -= curFlow[sink];
        edges[e.rev].cap += curFlow[sink];
        u = e.from;
    }
    return true;
}

void MCMF() {
    int minCost = 0, maxFlow = 0;
    while(BelFord(minCost, maxFlow));
    if (maxFlow < V) puts("N");
    else cout << minCost << endl;
}

int main() {    
    while (cin >> V && V) {
        init();
        MCMF();
    }
    
    return 0;
}