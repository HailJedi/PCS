#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int R, C;
char matrix[17][17];
int vis[30];
string res;
int sum;

/*
void get_max_str(string &self, string &comp) {
    if (self.length() > comp.length()) return;
    if (comp.length() > self.length()) { self = comp; return; }
    for (int i = 0; i < (int)self.length(); i++) {
        if (self[i] != comp[i]) {
            if (self[i] < comp[i]) self = comp;
            return;
        }
//            return (int)self[i] > (int)comp[i] ? self : comp;
    }
//    return self;
}
 */

const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

#define ID(r, c) (r*C+c)
#define is_in_bound(r, c) (r < R && c < C && r >= 0 && c >= 0)
int update[30];
int rst_pth;

int rest_path(int r, int c) {
    memcpy(update, vis, sizeof(update));
    int res = 0;
    int que[100], head = 0, tail = 0;
    que[tail++] = ID(r, c);
    
    while (head != tail) {
        int cur = que[head++];
        int cr = cur / C, cc = cur % C;
        for (int i = 0; i < 4; i++) {
            int nr = cr + dr[i], nc = cc + dc[i];
            if (is_in_bound(nr, nc) && matrix[nr][nc] != '#' && !update[ID(nr, nc)]) {
                que[tail++] = ID(nr, nc);
                update[ID(nr, nc)] = 1;
                res++;
            }
        }
    }
    
    return res;
}

void solve(int r, int c, string _str) {
    int rst_pth = rest_path(r, c);
    if (rst_pth + (int)_str.length() < (int)res.length()) return;
    if (rst_pth + (int)_str.length() == (int)res.length() && _str + "z" < res) return;
    
//    _str.push_back(matrix[r][c]);
    
    bool update = false;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (is_in_bound(nr, nc) && matrix[nr][nc] != '#' && !vis[ID(nr, nc)]) {
            update = true;
            vis[ID(nr, nc)] = 1;
            solve(nr, nc, _str + matrix[nr][nc]);
            vis[ID(nr, nc)] = 0;
        }
    }
//        get_max_str(res, _str);
    if (!update)
        if (res.length() < _str.length() || (res.length() == _str.length() && res < _str)) res = _str;
    
//    _str.pop_back();
}

void debug() {
    for (int i = 0; i < R; i++) {
        cout << matrix[i];
        cout << endl;
    }
}

int main () {
    ios::sync_with_stdio(false);
    
//    freopen("result.txt", "w", stdout);
    
//    cout << ("" < "123") << endl;
    
    while (cin >> R >> C && R && C) {
//        memset(matrix, '#', sizeof(matrix));
        
        for (int i = 0; i < R; i++)
            cin >> matrix[i];
        
//        debug();
        
//        cout << rest_path(1, 3) << endl << endl;
        res.clear();
        
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (matrix[i][j] != '#') {
                    memset(vis, 0, sizeof(vis));
                    string t = ""; t += matrix[i][j];
                    vis[ID(i, j)] = 1;
                    solve(i, j, t);
                }
        
        
        cout << res << endl;
    }
}
