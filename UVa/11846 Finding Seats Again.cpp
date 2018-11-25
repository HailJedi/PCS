#include <iostream>
#include <cstring>
using namespace std;

char seats[20][20];
char ans[20][20];
int n, k;

bool solve(int id, char grp) {
    
    while (ans[id/n][id%n] != '.') id++;
    
    if (id == n * n) return true;
    
    int cr = id / n, cc = id % n, lim_c = n;
//    cout << cr << ' ' << cc << endl;
    
    for (int r = cr; r < n; r++) {
        for (int c = cc; c < lim_c; c++) {
            
            if (ans[r][c] != '.') { lim_c = c; break; }
            
            int sum = (r - cr + 1) * (c - cc + 1);
            if (sum > 9) { lim_c = c; break; }
            
            int num = 10;
            bool over = false;
            for (int i = cr; i <= r; i++) {
                for (int j = cc; j <= c; j++) {
                    if (seats[i][j] != '.') {
                        if (num != 10) over = true;
                        num = seats[i][j] - '0';
//                        cout << num << endl;
                    }
                } if (over) break;
            } if (over) { lim_c = c; break; }
            
            if (num < sum) { lim_c = c; break; }
            if (num > sum) continue;
            
//            cout << grp << endl;
            
            for (int i = cr; i <= r; i++)
                for (int j = cc; j <= c; j++)
                    ans[i][j] = grp;
            
            if (solve(id + c - cc + 1, grp + 1))
                return true;
            
            for (int i = cr; i <= r; i++)
                for (int j = cc; j <= c; j++)
                    ans[i][j] = '.';
        }
    }
    
    
    return false;
}


int main() {
//    freopen("result.txt", "w",stdout);
    
    ios::sync_with_stdio(false);
    
    while (cin >> n >> k && n && k) {
        for (int i = 0; i < n; i++)
            cin >> seats[i];
        
//        for (int i = 0; i < n; i++)
//            cout << seats[i] << endl;
        
//        memcpy(ans, seats, sizeof(ans));
        memset(ans, '.', sizeof(ans));
        
        solve(0, 'A');
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << ans[i][j];
            cout << endl;
        }
            
    }
    
    return 0;
}
