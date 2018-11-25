#include <iostream>
using namespace std;

const int maxn = 100000 + 5;
int s, n, x[maxn*3], cnt[maxn], ok[maxn*2];

int main() {
//    freopen("result.txt", "w", stdout);
    
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    while (T--) {
        cin >> s >> n;
        
        fill (x, x+n+2*s, -1);
        for (int i = 0; i < n; i++) cin >> x[i+s];
        
        int tot = 0;
        fill(cnt+1, cnt+s+1, 0);
        fill(ok, ok+n+s+1, 0);
        
        for (int i = 0; i < n+s+1; i++) {
            if (tot == s) ok[i] = 1;
            if (i < s && tot == i) ok[i] = 1;
            if (i > n && tot == n+s-i) ok[i] = 1;
            
            if (i == n+s) break;
            if (x[i] != -1 && --cnt[x[i]] == 0) tot--;
            if (x[i+s] != -1 && cnt[x[i+s]]++ == 0) tot++;
        }
        
        int ans = 0;
        for (int i = 0; i < s; i++) {
            int valid = 1;
            for (int j = i; j < n+s+1; j += s)
                if (!ok[j]) valid = 0;
            if (valid) ans++;
        }
        if (ans == n+1) ans = s;
        cout << ans << endl;
    }
    return 0;
}
