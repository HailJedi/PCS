#include <iostream>
#include <algorithm>
#include <cstring>
#define maxn 50+5
#define INF 1000000000
using namespace std;

int l, n;
int len[maxn], s[maxn], cst[maxn][maxn];

int cost(int l, int r) {
    int &res = cst[l][r];
    if (res != -1) return res;
    if (l + 1 == r) return res = 0;
    res = INF;
    for (int mid = l + 1; mid <= r-1; mid++)
        res = min(res, cost(l, mid)+cost(mid, r) + len[r] - len[l]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    
    while(cin >> l >> n && l) {
        for (int i = 1; i <= n; i++) cin >> len[i]; len[0] = 0; len[n+1] = l;
        memset(cst, -1, sizeof(cst));
        cout << "The minimum cutting is " << cost(0, n+1) << '.' << endl;
    }
    return 0;
}
