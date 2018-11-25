#include <iostream>
#include <ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

const int maxn = 1000010;
int A[maxn], last[maxn];
hash_map<int, int> cur;

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        cur.clear();
        for (int i = 0; i < n; i++) {
            cin >> A[i];
            if (!cur.count(A[i])) last[i] = -1;
            else last[i] = cur[A[i]];
            cur[A[i]] = i;
        }
        
        int L = 0, R = 0, ans = 0;
        while (R < n) {
            while (R < n && last[R] < L) R++;
            ans = max(ans, R - L);
            L++;
        }
        cout << ans << endl;
    }
    return 0;
}

