#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int n;
char board[8][8];
char ans[7][7];
const string slash = "/\\";

bool qualified(int cr, int cc) {
    return (board[cr][cc] == '0' || board[cr][cc] >= '5')
    && (board[cr+1][cc+1] == '0' || board[cr+1][cc+1] >= '5')
    && (board[cr+1][cc] == '0' || board[cr+1][cc] >= '5')
    && (board[cr][cc+1] == '0' || board[cr][cc+1] >= '5');
}
#define ID(r, c) (r*(n+1)+c)
#define out_of_bound(r, c) (r > n || c > n || r < 0 || c < 0)
const int dr[] = {1, 1, -1, -1};
const int dc[] = {1, -1, 1, -1};

bool exist_circle() {
    queue<int> que;
    int mark[64];
    memset(mark, 0, sizeof(mark));
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) if (!mark[ID(i, j)]) {
            mark[ID(i, j)] = 1;
            
            que.push(ID(i, j));
            int fa[64]; memset(fa, -1, sizeof(fa));
            
            while (!que.empty()) {
                int c = que.front(); que.pop();
                int cr = c / (n+1), cc = c % (n+1);
                
                for (int i = 0; i <= 3; i++) {
                    int nr = cr + dr[i], nc = cc + dc[i];
                    
                    if (out_of_bound(nr, nc)) continue;
                    
                    if (ID(nr, nc) == fa[ID(cr, cc)]) continue;
                    
                    if ((i == 0 && ans[cr][cc] == '\\') || (i == 1 && ans[cr][cc-1] == '/') || (i == 2 && ans[cr-1][cc] == '/') || (i == 3 && ans[cr-1][cc-1] == '\\')) {
                        
                        if (fa[ID(nr, nc)] != -1) return true;
                        
                        que.push(ID(nr, nc));
                        fa[ID(nr, nc)] = ID(cr, cc);
                        mark[ID(nr, nc)] = 1;
                    }
                }
            }
        }
    }
    return false;
}

bool solve(int id) {
    
    if (id == n * n) return !exist_circle();
    
    int cr = id / n, cc = id % n;
    
    char cpy_brd[8][8]; memcpy(cpy_brd, board, sizeof(cpy_brd));
    
    if ('2' <= cpy_brd[cr][cc] && cpy_brd[cr][cc] <= '4') return false; // cut #1
    if (cpy_brd[cr][cc+1] == '3' || cpy_brd[cr][cc+1] == '4') return false; // cut #2
    if (cpy_brd[cr+1][cc] == '4') return false; // cut #3
    
    if (!(cc == n-1 && cpy_brd[cr][cc+1] == '1') || cpy_brd[cr][cc+1] == '2' || cpy_brd[cr+1][cc] == '3') { // cut #4
    
        if (cpy_brd[cr][cc] > '0' && cpy_brd[cr+1][cc+1] > '0') {
            board[cr][cc] -= 1; board[cr+1][cc+1] -= 1;
            ans[cr][cc] = '\\';
            if (solve(id+1) && qualified(cr, cc)) return true;
        }
        
    }
    
    memcpy(board, cpy_brd, sizeof(board));
    
    if (cpy_brd[cr][cc] == '1') return false; // cut #5
    if (cc == n-1 && cpy_brd[cr][cc+1] == '2') return false; // cut #6
    if (cr >= 1 && cc >= 1)
        if (ans[cr-1][cc-1] == '/' && ans[cr][cc-1] == '\\' && ans[cr-1][cc] == '\\') return false; // cut #7
    
    if (cpy_brd[cr+1][cc] > '0' && cpy_brd[cr][cc+1] > '0') {
        board[cr+1][cc] -= 1; board[cr][cc+1] -= 1;
        ans[cr][cc] = '/';
        if (solve(id+1) && qualified(cr, cc)) return true;
    }
    
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    string in;
    while (T--) {
        cin >> n;
        for (int i = 0; i <= n; i++) {
            cin >> in;
            for (int j = 0; j <= n; j++) {
                if (in[j] == '.') in[j] = '9';
                board[i][j] = in[j];
            }
        }
        solve(0);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << ans[i][j];
            cout << endl;
        }
    }
    return 0;
}

