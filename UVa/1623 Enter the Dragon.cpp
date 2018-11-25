#include <cstdio>
#include <set>
#include <cstring>
using namespace std;

const int maxn = 1000010;
int last[maxn];
int ans[maxn], real_ans[maxn];
set<int> days;

int main() {
//    freopen("write.txt", "w", stdout);
    int n, m;
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int t; bool ok = true;
        memset(last, 0, sizeof(last));
        memset(ans, 0, sizeof(ans));
        days.clear();
        for (int i = 0; i < m; i++) {
            scanf("%d", &t);
            if (!ok) continue;
            if (!t) {
                days.insert(i);
            } else {
                ans[i] = -1;
                set<int>::iterator it = days.lower_bound(last[t]);
                if (it == days.end()) { ok = false; continue; }
                ans[*it] = t; last[t] = i; days.erase(it);
            }
        }
        if (!ok) puts("NO");
        else {
            puts("YES"); int cnt = 0;
            for (int i = 0; i < m; i++)
                if (~ans[i]) real_ans[++cnt] = ans[i];
            for (int i = 1; i < cnt; i++)
                printf("%d ", real_ans[i]);
            printf("%d\n", real_ans[cnt]);
        }
    }
}
