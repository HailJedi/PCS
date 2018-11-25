#include <cstdio>
#include <algorithm>
#include <vector>
#define maxn 100000+5
using namespace std;

int n, T;
vector<int> sub[maxn];

int dp(int p) {
    if (sub[p].empty()) return 1;
    int k = (int)sub[p].size();
    vector<int> d;
    for (int i = 0; i < k; i++)
        d.push_back(dp(sub[p][i]));
    sort(d.begin(), d.end());
    int c = (k*T-1)/100+1;
    int ans = 0;
    for (int i = 0; i < c; i++)
        ans += d[i];
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &T) == 2 && n && T) {
        for (int i = 0; i <= n; i++) sub[i].clear();
        for (int i = 1; i <= n; i++) {
            int s; scanf("%d", &s);
            sub[s].push_back(i);
        }
        printf("%d\n", dp(0));
    }
    return 0;
}
