#include <iostream>
#include <queue>
#include <cstring>
#include <map>

using namespace std;

namespace data_structure {
    
    // 0 1 2 3 4 5 6
    // E W B R W B R
    
    // 0 1 2 3
    // E W B R
    
    const int dc[4] = { 0, 1, -1, 0 }; // up right left down
    const int dr[4] = { -1, 0, 0, 1 };
    
    const int rota[7][2] = { // first up & down, then left & right
        {0, 0},
        {6, 2},
        {3, 1},
        {2, 4},
        {5, 3},
        {4, 6},
        {1, 5}
    };
    
    const int cubics[] = { 0, 1, 2, 3, 1, 2, 3 };
    
    struct Status {
        int p[3][3], r, c, h;
        Status(const int q[3][3], int r, int c, int h) : r(r), c(c), h(h) {
            memcpy(p, q, sizeof(p));
        }
    };
    
} using namespace data_structure;

namespace declarations {
    
    //const int max_color = 262144;
    const int max_number = 40353607;
    int ec, er;
    int tc, tr;
    int tar[3][3]; // 4进制
    int src[3][3]; // 7进制
    int source;
    map<char, int> c2i;
    bool vis_by[2][max_number];
    int dist[max_number];
    int temp[3][3];
    queue<Status> q[2];
    
} using namespace declarations;

namespace processors {
    
    void rot(int p[3][3], int pr, int pc, int r, int c, int dir) {
        swap(p[r][c], p[pr][pc]);
        int id = p[r][c]; dir = min(dir, 3 - dir);
        p[r][c] = rota[id][dir];
    }
    
    bool are_same(int p[3][3], int q[3][3]) {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                if (cubics[p[i][j]] != cubics[q[i][j]])
                    return false;
        return true;
    }
    
    int num_hash(int p[3][3]) {
        int res = 0;
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                res = res * 7 + p[i][j];
        return res;
    }
    
    void iterate(int r, int c) {
        if (r == 3) {
            int end = num_hash(temp);
            q[1].push(Status(temp, tr, tc, end));
            vis_by[1][end] = 1;
            dist[end] = 0;
            return;
        }
        
        int nr = (r * 3 + c + 1) / 3;
        int nc = (r * 3 + c + 1) % 3;
        
        temp[r][c] = tar[r][c];
        
        iterate(nr, nc);
        
        if (tar[r][c] != 0) {
            temp[r][c] = tar[r][c] + 3;
            iterate(nr, nc);
        }
    }
    
} using namespace processors;

namespace main_functions {
    
    int bfs() {
        if (are_same(tar, src)) return 0;
        
        while (!q[0].empty()) q[0].pop();
        while (!q[1].empty()) q[1].pop();
        source = num_hash(src);
        vis_by[0][source] = 1; dist[source] = 0;
        q[0].push(Status(src, er, ec, source));
        
        iterate(0, 0);
        
        int step = 0;
        
        while (!q[0].empty() || !q[1].empty()) {
            for (int i = 0; i <= 1; i++) {
                int lim = (int)q[i].size();
                
//                if (step > 17 && i == 0) continue;
//                if (step > 13 && i == 1) continue;
                if (step > 30) return -1;
                bool update = false;
                
                while (lim--) {
                    const Status cur = q[i].front(); q[i].pop();
                    
                    const int r = cur.r, c = cur.c, cur_id = cur.h;
                    int cpy[3][3]; memcpy(cpy, cur.p, sizeof(cpy));
                    
                    for (int dir = 0; dir <= 3; dir++) {
                        const int nr = r + dr[dir];
                        const int nc = c + dc[dir];
                        
                        if (nr > 2 || nc > 2 || nr < 0 || nc < 0) continue;
                        
                        rot(cpy, nr, nc, r, c, dir);
                        
                        const int int_id = num_hash(cpy);
                        
                        // TO DO
                        if (!vis_by[i][int_id]) {
                            if (vis_by[i^1][int_id]) {
                                int res = dist[int_id] + dist[cur_id] + 1;
                                return res <= 30 ? res : -1;
                                //return res;
                            }
                            
                            vis_by[i][int_id] = 1;
                            dist[int_id] = dist[cur_id] + 1;
                            q[i].push(Status(cpy, nr, nc, int_id));
                            update = true;
                            // END
                        }
                        
                        rot(cpy, r, c, nr, nc, dir);
                    }
                }
                
                if (update) step++;
            }
        }
        return -1;
    }
    
    void solve() {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++) src[i][j] = 1;
        memset(vis_by, 0, sizeof(vis_by));
        fill(dist, dist + max_number, 31);
        src[er][ec] = 0;
        cout << bfs() << endl;
    }
    
} using namespace main_functions;

int main() {
    
    c2i['E'] = 0; c2i['W'] = 1; c2i['B'] = 2; c2i['R'] = 3;
    
    while (cin >> ec >> er && ec && er) {
        ec--; er--;
        char t;
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                cin >> t;
                tar[i][j] = c2i[t];
                if (t == 'E') { tc = j; tr = i; }
            }
        }
        solve();
    }
    
    return 0;
}
