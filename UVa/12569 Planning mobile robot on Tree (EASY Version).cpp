#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

// declarations
int V, Obs, S, T;
vector<int> tree_pos[15];
struct Status {
    int _pos[15], is_ocpy[15], hsh;
    Status(int pos[15], int ocpy[15], int h) : hsh(h) {
        memcpy(_pos, pos, sizeof(_pos));
        memcpy(is_ocpy, ocpy, sizeof(is_ocpy));
    }
};
int p[15], o[15];
const int max_status = 11957422;
int pth_1[max_status], pth_2[max_status];
int last[max_status];
int head_hsh;
int step;

// buff functions
void add_edge(int u, int v) {
    tree_pos[u].push_back(v);
    tree_pos[v].push_back(u);
}

int hash_val(int p[15]) {
    int res = 0;
    for (int i = 0; i < V; i++) {
        res = res * 3 + p[i];
    }
    return res;
}
int kase = 0;
void output(int node) {
    if (node == head_hsh) { cout << "Case " << ++kase << ": " << step << endl; return; }
    step++; output(last[node]);
    cout << pth_1[node]+1 << ' ' << pth_2[node]+1 << endl;
}


// main algorithms
int vis[max_status];

void bfs() {
    
    step = 0;
    
    if (T == S) {
        output(head_hsh);
//        cout << "ops!\n";
        return;
    }
    
    queue<Status> q; head_hsh = hash_val(o);
    q.push(Status(p, o, head_hsh));
    memset(vis, 0, sizeof(vis));
    
    while (!q.empty()) {
        
        Status cur_stat = q.front(); q.pop();
//        cout << "trying\n";
        // try to move obstacles & robot
        for (int id = 0; id <= Obs; id++) {
            
            int _pos = cur_stat._pos[id];
            
            for (int i = 0; i < tree_pos[_pos].size(); i++) {
                
                int nxt_pos = tree_pos[_pos][i];
                if(cur_stat.is_ocpy[nxt_pos]) continue;
                
                int cpy_pos[15]; memcpy(cpy_pos, cur_stat._pos, sizeof(cpy_pos));
                cpy_pos[id] = nxt_pos;
                
                int cpy_ocpy[15]; memcpy(cpy_ocpy, cur_stat.is_ocpy, sizeof(cpy_ocpy));
                cpy_ocpy[nxt_pos] = (id == Obs ? 2 : 1); cpy_ocpy[_pos] = 0;
                
                int nxt_hsh = hash_val(cpy_ocpy);
                
                if (vis[nxt_hsh]) continue;
                vis[nxt_hsh] = 1;
                q.push(Status(cpy_pos, cpy_ocpy, nxt_hsh));
                
                pth_1[nxt_hsh] = cur_stat._pos[id];
                pth_2[nxt_hsh] = nxt_pos;
                last[nxt_hsh] = cur_stat.hsh;
                
                if (id == Obs && nxt_pos == T) {
                    output(nxt_hsh);
                    return;
                }
            }
        }
    }
    
//    cout << "failed\n";
    step = -1;
    output(head_hsh);
}

void solve() {
    bfs();
    cout << endl;
}

void clear() {
    memset(o, 0, sizeof(o));
    memset(p, -1, sizeof(p));
    for (int i = 0; i < V; i++)
        tree_pos[i].clear();
}

void debug() {
    for (int i = 0; i < V; i++)
        cout << i << ' ' << p[i] << ' ' << o[i] << endl;
    cout << S << ' ' << T << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t--) {
        cin >> V >> Obs >> S >> T;
        clear();
        T--; S--; o[S] = 2;
        for (int i = 0; i < Obs; i++) {
            cin >> p[i]; p[i]--;
            o[p[i]] = 1;
        }
        p[Obs] = S;
        for (int i = 0; i < V-1; i++) {
            int u, v;
            cin >> u >> v; u--; v--;
            add_edge(u, v);
        }
//        debug();
        solve();
    }
}